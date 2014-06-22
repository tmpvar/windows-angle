{

  'targets' : [
    {
      'target_name' : 'libGLESv2',
      'type' : 'static_library',
      'includes' : [
        'deps/angle/build/common.gypi'
      ],


      'include_dirs' : [
        'deps/angle/include',
        'deps/angle/src',
        'src/shim',
      ],
      'defines' : [
        'ANGLE_COMPILE_OPTIMIZATION_LEVEL',
        'ANGLE_COMMIT_HASH="tmpvar"',
        'ANGLE_COMMIT_HASH_SIZE=6',
        'angle_use_commit_id=0',
        'GL_GLEXT_PROTOTYPES'
      ],
      'sources' : [
        'deps/angle/src/libGLESv2/Buffer.cpp',
        'deps/angle/src/libGLESv2/Context.cpp',
        'deps/angle/src/libGLESv2/DynamicHLSL.cpp',
        'deps/angle/src/libGLESv2/Fence.cpp',
        'deps/angle/src/libGLESv2/Float16ToFloat32.cpp',
        'deps/angle/src/libGLESv2/Framebuffer.cpp',
        'deps/angle/src/libGLESv2/FramebufferAttachment.cpp',
        'deps/angle/src/libGLESv2/HandleAllocator.cpp',
        'deps/angle/src/libGLESv2/Program.cpp',
        'deps/angle/src/libGLESv2/ProgramBinary.cpp',
        'deps/angle/src/libGLESv2/Query.cpp',
        'deps/angle/src/libGLESv2/Renderbuffer.cpp',
        'deps/angle/src/libGLESv2/RenderbufferProxySet.cpp',
        'deps/angle/src/libGLESv2/ResourceManager.cpp',
        'deps/angle/src/libGLESv2/Sampler.cpp',
        'deps/angle/src/libGLESv2/Shader.cpp',
        'deps/angle/src/libGLESv2/Texture.cpp',
        'deps/angle/src/libGLESv2/TransformFeedback.cpp',
        'deps/angle/src/libGLESv2/Uniform.cpp',
        'deps/angle/src/libGLESv2/VertexArray.cpp',
        'deps/angle/src/libGLESv2/angletypes.cpp',
        'deps/angle/src/libGLESv2/formatutils.cpp',
        'deps/angle/src/libGLESv2/libGLESv2.cpp',
        'deps/angle/src/libGLESv2/precompiled.cpp',
        'deps/angle/src/libGLESv2/queryconversions.cpp',
      ],
    },
    {
      'target_name' : 'libEGL',
      'type' : 'static_library',
      'dependencies' : [
        'libGLESv2'
      ],
      'includes' : [
        'deps/angle/build/common.gypi'
      ],
      'include_dirs' : [
        'deps/angle/include',
        'deps/angle/src',
        'src/shim',
        'libGLESv2'
      ],

      'defines' : [
        'ANGLE_COMPILE_OPTIMIZATION_LEVEL',
        'ANGLE_COMMIT_HASH="tmpvar"',
        'ANGLE_COMMIT_HASH_SIZE=6',
        'angle_use_commit_id=0',
        'GL_GLEXT_PROTOTYPES'
      ],

      'sources' : [
        'deps/angle/src/libEGL/Config.cpp',
        'deps/angle/src/libEGL/Display.cpp',
        'deps/angle/src/libEGL/Surface.cpp',
        'deps/angle/src/libEGL/libEGL.cpp',
      ]
    }
  ]
}