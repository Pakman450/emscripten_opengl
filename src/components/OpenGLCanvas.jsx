import React from 'react'
import { useEffect } from 'react';
export default function OpenGLCanvas({ exampleProp }) {
  useEffect(() => {
    const canvas = document.querySelector("#canvas")
    window.Module = { canvas };

    const script = document.createElement('script');
    script.src = 'src/hello_triangle.js';
    script.async = true;
    document.body.appendChild(script);
    console.log(window.Module)
    return () => {
      document.body.removeChild(script);
    };
  }, []);

  console.log(exampleProp)
  
  return (
    <canvas className="fullwindow" id="canvas" onContextMenu={(e) => e.preventDefault()}></canvas>
  )
}
