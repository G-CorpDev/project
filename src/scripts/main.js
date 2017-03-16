import React from 'react';
import ReactDOM from 'react-dom';

import style from '../scss/main.scss';

import Test from './modules/Test.js'


ReactDOM.render((
        <div className="main">
            <p>This is main, Hello World!</p>
            <Test />
        </div>
    ), document.getElementById('root')
);