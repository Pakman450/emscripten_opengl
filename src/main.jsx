import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.jsx'
import './index.css'

ReactDOM.createRoot(document.getElementById('root')).render(

  // For some reason, turning on Strict Mode
  // crashes the opengl wasm so they are commented
  // out
  // <React.StrictMode>
    <App />
  // </React.StrictMode>,
)
