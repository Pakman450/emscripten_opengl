import OpenGLCanvas from './components/OpenGLCanvas';
function App() {

  return (
    <>
      <div className="navbar bg-base-100">
      <div className="dropdown">
        <div tabIndex={0} role="button" className="btn m-1">Load</div>
        <ul tabIndex={0} className="dropdown-content menu bg-base-100 rounded-box z-[1] w-52 p-2 shadow">
          <li><a>Load Molecules</a></li>
          <li><a>Item 2</a></li>
        </ul>
      </div>

      </div>
      <div className='bg-base-200 flex justify-center'>
        <OpenGLCanvas exampleProp={258}/>
      </div>
    </>
  );
}

export default App;
