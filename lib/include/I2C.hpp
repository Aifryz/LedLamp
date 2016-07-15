namespace I2C
{
    //bool is_i2c_driver<T>
    //everything works on errorcodes
    template<class SCLPinDriver, class SDAPinDriver>
    struct BitBangDriver
    {
        static_assert(is_PinDriver<SCLPinDriver>::value && is_PinDriver<SDAPinDriver>::value,"Bad pin drivers")
    };
    struct TwiDriver
    {
        
    };
}