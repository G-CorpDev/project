import React, {Component} from 'react';

import Auth from './modules/Auth.js'
import Menu from './modules/Menu.js'

class App extends Component {
    constructor(props) {
        super(props);
    }

    render(){
        return (
            <div className="app">
                <Menu />
                <span className="header">G-corp workout</span>
                <Auth />
                <div className="bg"  style={{background: 'url(src/img/bg_1.jpg) no-repeat 0 0'}}></div>
            </div>
        );
    }
}

export default App;