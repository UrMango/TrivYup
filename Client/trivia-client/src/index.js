import React from 'react';
import ReactDOM from 'react-dom/client';
import { Provider } from 'react-redux';
import { configureStore } from '@reduxjs/toolkit';
import {BrowserRouter as Router} from 'react-router-dom';
import allReducers from "./reducers/index";
import App from './App';

const root = ReactDOM.createRoot(document.getElementById('root'));
const store = configureStore({ reducer: allReducers, devTools: true});

root.render(
  <React.StrictMode>
    <Provider store={store}>
      <Router>
        <App />
      </Router>
    </Provider>
  </React.StrictMode>
);
