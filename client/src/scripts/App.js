import React, {Component} from 'react';

import Page from './modules/Page.js'

class App extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className="app">
                <Page />
                <div className="bg" style={{background: 'url(src/img/bg_6.jpg) no-repeat 0 0'}}></div>
            </div>
        );
    }
}

export default App;