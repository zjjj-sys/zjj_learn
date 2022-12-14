#define _NAME(n, s) n##_##s
#if MULTI_SENSOR
#define NAME(n) _NAME(n, JXF22_MIPI)
#else
#define NAME(n) n
#endif

unsigned int NAME(ImageParamWdr)[4] =
{
        0x16, 0x50, 0x5a, 0x10 //contrast,brightness, saturation, sharpness default value
};

unsigned int NAME(contrastWdr)[12] =
{
        0x16, 0x15, 0x15, 0x15, 0x15, 0x15, 0x14, 0x14, 0x16, 0x18, 0x18, 0x18
};

unsigned int NAME(saturationWdr)[12] =
{
        0x5a, 0x58, 0x4a, 0x40, 0x30, 0x2c, 0x28, 0x24, 0x18, 0x18, 0x10, 0x10
};

unsigned int NAME(sharpnessWdr)[12] =
{
        0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x0, 0x0, 0x0, 0x0
};

unsigned int NAME(MirrorFlipBayerFormatWdr)[4] =
{
        2, 1, 3, 0
};

unsigned int NAME(AwbGainWdr)[4][3] = {
    {0x179, 0x152, 0x346},  // a-2600k
    {0x20d, 0x15a, 0x2b0},  // 4100k
    {0x26b, 0x168, 0x241},  // 6600k
    {0x322, 0x155, 0x19f},  // 7500K
};
