import React from 'react'
import { useEffect } from 'react';

export default function OpenGLCanvas({ exampleProp }) {
  useEffect(() => {
    const canvas = document.querySelector("#canvas")

    window.Module = { 
      canvas, 
      arguments: ['arg1', 'arg2', 'arg3'],
      onRuntimeInitialized: ()=>{
        console.log('Emscripten module intialized');
        console.log('Module before script load:', window.Module);
      }
      
    };

    const script = document.createElement('script');
    script.src = 'src/cpp/em_main.js';
    script.async = true;



    document.body.appendChild(script);

    return () => {
      document.body.removeChild(script);
    };
  }, []);

  console.log(exampleProp)
  
  return (
    <canvas width="800" height="800" className="fullwindow" id="canvas" onContextMenu={(e) => e.preventDefault()}></canvas>
  )
}
