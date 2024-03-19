static const DWORD copy_descriptors_code_dxbc[] =
{
    0x43425844, 0x52d2c2d3, 0xaf60e190, 0xb897944f, 0x4a6a6653, 0x00000001, 0x00000650, 0x00000003,
    0x0000002c, 0x0000003c, 0x0000004c, 0x4e475349, 0x00000008, 0x00000000, 0x00000008, 0x4e47534f,
    0x00000008, 0x00000000, 0x00000008, 0x58454853, 0x000005fc, 0x00050050, 0x0000017f, 0x0100086a,
    0x04000059, 0x00208e46, 0x00000000, 0x00000001, 0x04000059, 0x00208e46, 0x00000001, 0x00000001,
    0x04000059, 0x00208e46, 0x00000002, 0x00000001, 0x0300005a, 0x00106000, 0x00000000, 0x0300005a,
    0x00106000, 0x00000001, 0x0300005a, 0x00106000, 0x00000002, 0x0300085a, 0x00106000, 0x00000003,
    0x04001858, 0x00107000, 0x00000000, 0x00005555, 0x04001858, 0x00107000, 0x00000001, 0x00004444,
    0x04001858, 0x00107000, 0x00000002, 0x00003333, 0x04000858, 0x00107000, 0x00000003, 0x00005555,
    0x040000a2, 0x00107000, 0x00000004, 0x00000004, 0x030000a1, 0x00107000, 0x00000005, 0x04001858,
    0x00107000, 0x00000006, 0x00005555, 0x0300009d, 0x0011e000, 0x00000000, 0x0400009e, 0x0011e000,
    0x00000001, 0x00000010, 0x0300009d, 0x0011e000, 0x00000002, 0x02000068, 0x00000002, 0x0400009b,
    0x00000001, 0x00000001, 0x00000001, 0x0600001c, 0x00100012, 0x00000000, 0x0020800a, 0x00000000,
    0x00000000, 0x06000036, 0x00100022, 0x00000000, 0x0020800a, 0x00000001, 0x00000000, 0x06000036,
    0x00100042, 0x00000000, 0x0020800a, 0x00000002, 0x00000000, 0x05000036, 0x00100082, 0x00000000,
    0x00004001, 0x00000000, 0x070000a6, 0x0011e0f2, 0x00000002, 0x00004001, 0x00000000, 0x00100e46,
    0x00000000, 0x90000048, 0x800000c2, 0x00155543, 0x001000f2, 0x00000000, 0x00004002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00107e46, 0x00000000, 0x00106000, 0x00000000, 0x00004001,
    0x00000000, 0x0500001c, 0x001000f2, 0x00000000, 0x00100e46, 0x00000000, 0x070000a6, 0x0011e0f2,
    0x00000002, 0x00004001, 0x00000010, 0x00100e46, 0x00000000, 0x90000048, 0x800000c2, 0x00155543,
    0x001000f2, 0x00000000, 0x00004002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00107e46,
    0x00000000, 0x00106000, 0x00000001, 0x00004001, 0x00000000, 0x0500001c, 0x001000f2, 0x00000000,
    0x00100e46, 0x00000000, 0x070000a6, 0x0011e0f2, 0x00000002, 0x00004001, 0x00000020, 0x00100e46,
    0x00000000, 0x90000048, 0x800000c2, 0x00155543, 0x001000f2, 0x00000000, 0x00004002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00107e46, 0x00000000, 0x00106000, 0x00000002, 0x00004001,
    0x00000000, 0x0500001c, 0x001000f2, 0x00000000, 0x00100e46, 0x00000000, 0x070000a6, 0x0011e0f2,
    0x00000002, 0x00004001, 0x00000030, 0x00100e46, 0x00000000, 0x8c00002d, 0x80000042, 0x00155543,
    0x00100012, 0x00000000, 0x00004002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00107e46,
    0x00000003, 0x0500001c, 0x00100042, 0x00000000, 0x0010000a, 0x00000000, 0x8b0000a7, 0x80002302,
    0x00199983, 0x00100012, 0x00000001, 0x00004001, 0x00000000, 0x00004001, 0x00000000, 0x00107006,
    0x00000004, 0x0500001c, 0x00100082, 0x00000000, 0x0010000a, 0x00000001, 0x8c00002d, 0x800000c2,
    0x00111103, 0x00100012, 0x00000000, 0x00004002, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00107e46, 0x00000001, 0x8c00002d, 0x800000c2, 0x000cccc3, 0x00100022, 0x00000000, 0x00004002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00107e16, 0x00000002, 0x070000a6, 0x0011e0f2,
    0x00000002, 0x00004001, 0x00000040, 0x00100e46, 0x00000000, 0x890000a5, 0x800002c2, 0x00199983,
    0x001000f2, 0x00000000, 0x00004001, 0x00000000, 0x00107e46, 0x00000005, 0x070000a6, 0x0011e0f2,
    0x00000002, 0x00004001, 0x00000050, 0x00100e46, 0x00000000, 0x90000047, 0x800000c2, 0x00155543,
    0x00100012, 0x00000000, 0x00004002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00107006,
    0x00000006, 0x00106000, 0x00000003, 0x00004001, 0x3f19999a, 0x0500001c, 0x00100012, 0x00000000,
    0x0010000a, 0x00000000, 0x070000a6, 0x0011e0f2, 0x00000002, 0x00004001, 0x00000060, 0x00100006,
    0x00000000, 0x90000047, 0x800000c2, 0x00155543, 0x00100012, 0x00000000, 0x00004002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00107006, 0x00000006, 0x00106000, 0x00000003, 0x00004001,
    0x3ecccccd, 0x0500001c, 0x00100012, 0x00000000, 0x0010000a, 0x00000000, 0x070000a6, 0x0011e0f2,
    0x00000002, 0x00004001, 0x00000070, 0x00100006, 0x00000000, 0x890000a5, 0x800002c2, 0x00199983,
    0x00100032, 0x00000000, 0x00004001, 0x00000000, 0x0011e046, 0x00000000, 0x890000a5, 0x800002c2,
    0x00199983, 0x001000c2, 0x00000000, 0x00004001, 0x00000008, 0x0011e406, 0x00000000, 0x070000a6,
    0x0011e0f2, 0x00000002, 0x00004001, 0x00000080, 0x00100e46, 0x00000000, 0x8b0000a7, 0x80008302,
    0x00199983, 0x001000f2, 0x00000000, 0x00004001, 0x00000000, 0x00004001, 0x00000000, 0x0011ee46,
    0x00000001, 0x070000a6, 0x0011e072, 0x00000002, 0x00004001, 0x00000090, 0x00100246, 0x00000000,
    0x0500001c, 0x00100012, 0x00000000, 0x0010003a, 0x00000000, 0x070000a6, 0x0011e0f2, 0x00000002,
    0x00004001, 0x0000009c, 0x00100006, 0x00000000, 0x070000a6, 0x0011e012, 0x00000002, 0x00004001,
    0x000000ac, 0x00004001, 0xdeadbeef, 0x0100003e,
};
#ifdef __GNUC__
#define UNUSED_ARRAY_ATTR __attribute__((unused))
#else
#define UNUSED_ARRAY_ATTR
#endif
UNUSED_ARRAY_ATTR static const D3D12_SHADER_BYTECODE copy_descriptors_dxbc = { copy_descriptors_code_dxbc, sizeof(copy_descriptors_code_dxbc) };
#undef UNUSED_ARRAY_ATTR