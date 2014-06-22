{
  'targets' : [{
    'target_name' : 'angle-static',
    'type' : 'static_library',
    'dependencies' : [
      'angle.gyp:libGLESv2',
      'angle.gyp:libEGL'
    ]
  }]
}