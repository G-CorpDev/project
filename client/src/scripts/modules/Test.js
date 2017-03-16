import React, {Component} from 'react';

class Test extends Component {
    constructor() {
        super();
        this.private_field = new Object();
    }

    getSeconds(){
        let date = new Date();
        return date.getSeconds();
    }

    getMinutes(){
        let date = new Date();
        return date.getMinutes();
    }

    render(){
        return (<div>Tick-tock~{this.getMinutes()}:{this.getSeconds()}</div>);
    }
}

export default Test;