#include "adc.h"

void Initialize_ADC(void) {
    // Select reference voltage
    ADMUX |= (0 << REFS1) | (1 << REFS0);           // AVCC with external capacitor at AREF pin

    // ADC must run between 50 and 200 khz to obtain maximum resolution (AtMega328p data sheet Sec 23.4)
    ADCSRA = (1 << ADPS2) | (1 << ADPS1);           // Set Pre-scalar PS = 64, ADC CLK = 8 Mhz (CPU_FREQ) / 64 (PSC) = 125 khz
    ADCSRA |= (1 << ADEN) | (1 << ADSC);            // Enable ADC and start a 'dummy' conversion to initialize the analog circuitry
    // 25 ADC clock cycles must elapse in order to fully set-up analog circuitry
    // This is about 0.2 ms with a pre-scalar value of 64.
}

/*
    Time to complete conversion (AtMega328p data sheet Sec 23.4)
        Nominal Conversion (Assuming ADC is fully setup): 13.5 ADC Cycles -> ~0.11 ms
*/
uint16_t ADC_Convert(uint8_t channel) {
    // Select ADC channel
    ADMUX = (ADMUX & 0xF0) | channel;               // Sets ADMUX to AVCC with external capacitor at AREF pin, then selects the channel
    ADCSRA |= 1 << ADSC;                            // Start conversion
	while ((ADCSRA & (1 << ADSC)) == 1){}           // Wait for the conversion to finish
	uint8_t adcl = ADCL;                            // Read ADCL register
	uint8_t adch = ADCH;                            // Read ADCH Register
	uint16_t val = ((adch << 8) | adcl) & 0x3FF;    // Combine into single 10 bit value, 0x3FF-> 0b11 1111 1111	 
	return val;
}

uint16_t Read_Potentiometer_1(void) {
    Potentiometer_1_Signal = ADC_Convert(Pot_1_Signal);
    return Potentiometer_1_Signal;
}

uint16_t Read_Potentiometer_2(void) {
    Potentiometer_2_Signal = ADC_Convert(Pot_2_Signal);
    return Potentiometer_2_Signal;
}

uint16_t Read_Potentiometer_3(void) {
    Potentiometer_3_Signal = ADC_Convert(Pot_3_Signal);
    return Potentiometer_3_Signal;
}

uint16_t Read_Potentiometer_4(void) {
    Potentiometer_4_Signal = ADC_Convert(Pot_4_Signal);
    return Potentiometer_4_Signal;
}

uint16_t Read_Ammeter_1(void) {
    Ammeter_1_Reading = ADC_Convert(Ammeter_1);
    return Ammeter_1_Reading;
}

uint16_t Read_Ammeter_2(void) {
    Ammeter_2_Reading = ADC_Convert(Ammeter_2);
    return Ammeter_2;
}