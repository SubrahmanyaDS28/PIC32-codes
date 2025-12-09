#ifndef __ENCODER_H__
    #define __ENCODER_H__

    void counts_to_ra_hms(uint32_t counts, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
    void counts_to_deg_dms(uint32_t counts, uint16_t *degrees, uint8_t *minutes, uint8_t *seconds);
    
    double EncoderToDEC(uint32_t counts);
    void DEC_To_DMS(double dec_deg, int16_t *deg, uint8_t *min, uint8_t *sec);
    double EncoderToRA(uint32_t counts);
    void RA_To_HMS(double ra_hr, int8_t *hour, uint8_t *min, uint8_t *sec);
    
    void Convert_RA_to_HMS_Centered_QEI1(uint16_t pos);
    void Convert_DEC_to_DMS_Centered_QEI2(int16_t pos);
    
    void Set_Select(uint8_t sel);
    uint8_t Read_EncoderBus(void);
    uint32_t Read_17bit_Encoder(uint8_t baseSelect);

#endif