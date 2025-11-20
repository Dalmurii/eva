#pragma once
#include <cstdint>

namespace eva {

enum class SHADER_STAGE : uint32_t {
    NONE                      = 0x00000000,
    VERTEX                    = 0x00000001,
    TESSELLATION_CONTROL      = 0x00000002,
    TESSELLATION_EVALUATION   = 0x00000004,
    GEOMETRY                  = 0x00000008,
    FRAGMENT                  = 0x00000010,
    ALL_GRAPHICS              = 0x0000001F,
    COMPUTE                   = 0x00000020,
    TASK                      = 0x00000040,
    MESH                      = 0x00000080,
    RAYGEN                    = 0x00000100,
    ANY_HIT                   = 0x00000200,
    CLOSEST_HIT               = 0x00000400,
    MISS                      = 0x00000800,
    INTERSECTION              = 0x00001000,
    CALLABLE                  = 0x00002000,
    ALL                       = 0x7FFFFFFF,
};
inline constexpr SHADER_STAGE operator|(SHADER_STAGE lhs, SHADER_STAGE rhs)         { return (SHADER_STAGE) ((uint32_t)lhs | (uint32_t)rhs); }
inline SHADER_STAGE& operator|=(SHADER_STAGE& lhs, SHADER_STAGE rhs)                { lhs = lhs | rhs; return lhs; }


enum class DESCRIPTOR_TYPE : uint32_t {
    SAMPLER                                 = 0,
    COMBINED_IMAGE_SAMPLER                  = 1,
    SAMPLED_IMAGE                           = 2,
    STORAGE_IMAGE                           = 3,
    UNIFORM_TEXEL_BUFFER                    = 4,
    STORAGE_TEXEL_BUFFER                    = 5,
    UNIFORM_BUFFER                          = 6,
    STORAGE_BUFFER                          = 7,
    UNIFORM_BUFFER_DYNAMIC                  = 8,
    STORAGE_BUFFER_DYNAMIC                  = 9,
    INPUT_ATTACHMENT                        = 10,
    INLINE_UNIFORM_BLOCK                    = 1000138000,
    ACCELERATION_STRUCTURE_KHR              = 1000150000,
    MUTABLE_EXT                             = 1000351000,
    SAMPLE_WEIGHT_IMAGE_QCOM                = 1000440000,
    BLOCK_MATCH_IMAGE_QCOM                  = 1000440001,
    PARTITIONED_ACCELERATION_STRUCTURE_NV   = 1000570000,
    MAX_ENUM                                = 0x7FFFFFFF,
};


enum class PIPELINE_STAGE : uint64_t {
    NONE                              =              0ULL,
    TOP_OF_PIPE                       =     0x00000001ULL,
    DRAW_INDIRECT                     =     0x00000002ULL,
    VERTEX_INPUT                      =     0x00000004ULL,
    VERTEX_SHADER                     =     0x00000008ULL,
    TESSELLATION_CONTROL_SHADER       =     0x00000010ULL,
    TESSELLATION_EVALUATION_SHADER    =     0x00000020ULL,
    GEOMETRY_SHADER                   =     0x00000040ULL,
    FRAGMENT_SHADER                   =     0x00000080ULL,
    EARLY_FRAGMENT_TESTS              =     0x00000100ULL,
    LATE_FRAGMENT_TESTS               =     0x00000200ULL,
    COLOR_ATTACHMENT_OUTPUT           =     0x00000400ULL,
    COMPUTE_SHADER                    =     0x00000800ULL,
    TRANSFER                          =     0x00001000ULL,
    BOTTOM_OF_PIPE                    =     0x00002000ULL,
    HOST                              =     0x00004000ULL,
    ALL_GRAPHICS                      =     0x00008000ULL,
    ALL_COMMANDS                      =     0x00010000ULL,
    COMMAND_PREPROCESS                =     0x00020000ULL,
    CONDITIONAL_RENDERING             =     0x00040000ULL,
    TASK_SHADER                       =     0x00080000ULL,
    MESH_SHADER                       =     0x00100000ULL,
    RAY_TRACING_SHADER                =     0x00200000ULL,
    FRAGMENT_SHADING_RATE_ATTACHMENT  =     0x00400000ULL,
    FRAGMENT_DENSITY_PROCESS          =     0x00800000ULL,
    TRANSFORM_FEEDBACK                =     0x01000000ULL,
    ACCELERATION_STRUCTURE_BUILD      =     0x02000000ULL,
#ifdef VULKAN_VERSION_1_3
    VIDEO_DECODE                      =     0x04000000ULL,
    VIDEO_ENCODE                      =     0x08000000ULL,
    ACCELERATION_STRUCTURE_COPY       =     0x10000000ULL,
    OPTICAL_FLOW                      =     0x20000000ULL,
    MICROMAP_BUILD                    =     0x40000000ULL,
    COPY                              =    0x100000000ULL,
    RESOLVE                           =    0x200000000ULL,
    BLIT                              =    0x400000000ULL,
    CLEAR                             =    0x800000000ULL,
    INDEX_INPUT                       =   0x1000000000ULL,
    VERTEX_ATTRIBUTE_INPUT            =   0x2000000000ULL,
    PRE_RASTERIZATION_SHADERS         =   0x4000000000ULL,
    CONVERT_COOPERATIVE_VECTOR_MATRIX = 0x100000000000ULL,
#endif
};
inline constexpr PIPELINE_STAGE operator|(PIPELINE_STAGE lhs, PIPELINE_STAGE rhs)   { return (PIPELINE_STAGE) ((uint64_t)lhs | (uint64_t)rhs); }


enum class ACCESS : uint64_t {
    NONE                                  =              0ULL,
    INDIRECT_COMMAND_READ                 =     0x00000001ULL,
    INDEX_READ                            =     0x00000002ULL,
    VERTEX_ATTRIBUTE_READ                 =     0x00000004ULL,
    UNIFORM_READ                          =     0x00000008ULL,
    INPUT_ATTACHMENT_READ                 =     0x00000010ULL,
    SHADER_READ                           =     0x00000020ULL,
    SHADER_WRITE                          =     0x00000040ULL,
    COLOR_ATTACHMENT_READ                 =     0x00000080ULL,
    COLOR_ATTACHMENT_WRITE                =     0x00000100ULL,
    DEPTH_STENCIL_ATTACHMENT_READ         =     0x00000200ULL,
    DEPTH_STENCIL_ATTACHMENT_WRITE        =     0x00000400ULL,
    TRANSFER_READ                         =     0x00000800ULL,
    TRANSFER_WRITE                        =     0x00001000ULL,
    HOST_READ                             =     0x00002000ULL,
    HOST_WRITE                            =     0x00004000ULL,
    MEMORY_READ                           =     0x00008000ULL,
    MEMORY_WRITE                          =     0x00010000ULL,
    COMMAND_PREPROCESS_READ               =     0x00020000ULL,
    COMMAND_PREPROCESS_WRITE              =     0x00040000ULL,
    COLOR_ATTACHMENT_READ_NONCOHERENT     =     0x00080000ULL,
    CONDITIONAL_RENDERING_READ            =     0x00100000ULL,
    ACCELERATION_STRUCTURE_READ           =     0x00200000ULL,
    ACCELERATION_STRUCTURE_WRITE          =     0x00400000ULL,
    FRAGMENT_SHADING_RATE_ATTACHMENT_READ =     0x00800000ULL,
    FRAGMENT_DENSITY_MAP_READ             =     0x01000000ULL,
    TRANSFORM_FEEDBACK_WRITE              =     0x02000000ULL,
    TRANSFORM_FEEDBACK_COUNTER_READ       =     0x04000000ULL,
    TRANSFORM_FEEDBACK_COUNTER_WRITE      =     0x08000000ULL,
#ifdef VULKAN_VERSION_1_3
    SHADER_SAMPLED_READ                   =    0x100000000ULL,
    SHADER_STORAGE_READ                   =    0x200000000ULL,
    SHADER_STORAGE_WRITE                  =    0x400000000ULL,
    VIDEO_DECODE_READ                     =    0x800000000ULL,
    VIDEO_DECODE_WRITE                    =   0x1000000000ULL,
    VIDEO_ENCODE_READ                     =   0x2000000000ULL,
    VIDEO_ENCODE_WRITE                    =   0x4000000000ULL,
    SHADER_BINDING_TABLE_READ             =  0x10000000000ULL,
    DESCRIPTOR_BUFFER_READ                =  0x20000000000ULL,
    OPTICAL_FLOW_READ                     =  0x40000000000ULL,
    OPTICAL_FLOW_WRITE                    =  0x80000000000ULL,
    MICROMAP_READ                         = 0x100000000000ULL,
    MICROMAP_WRITE                        = 0x200000000000ULL,
#endif
};
inline constexpr ACCESS operator|(ACCESS lhs, ACCESS rhs)       { return (ACCESS) ((uint64_t)lhs | (uint64_t)rhs); }



enum class IMAGE_LAYOUT : uint32_t {
    UNDEFINED                 = 0,
    GENERAL                   = 1,
    COLOR_ATTACHMENT          = 2,
    DEPTH_STENCIL_ATTACHMENT  = 3,
    DEPTH_STENCIL_READ_ONLY   = 4,
    SHADER_READ_ONLY          = 5,
    TRANSFER_SRC              = 6,
    TRANSFER_DST              = 7,
    PREINITIALIZED            = 8,
    PRESENT_SRC               = 1000001002,
    MAX_ENUM                  = 0x7FFFFFFF,
};

} // namespace eva