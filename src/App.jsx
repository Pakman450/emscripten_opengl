import { useEffect, useRef } from 'react';
import OpenGLCanvas from './components/OpenGLCanvas';
function App() {

  return (
    <>
      <div className="navbar bg-base-100">
        {/* <a className="btn btn-ghost text-xl">graph</a> */}
        <a className="btn btn-ghost text-xl"> Load </a>

      </div>
      <div className='bg-base-200 flex justify-center'>
        <OpenGLCanvas exampleProp={258}/>
      </div>
      <div>
        asdf
      </div>
    </>
  );
}

export default App;
