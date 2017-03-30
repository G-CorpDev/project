import React, {Component} from 'react';

import Auth from './Auth.js';
import Worksheet from './Worksheet.js';
import Menu from './Menu.js';

class Page extends Component {
    constructor(props) {
        super(props);
        this.state = {
            flip: "page--noflip",
            logged: true,
        }
    }

    flip(){
        let flip = this.state.flip==="page--noflip" ? "page--flip" : "page--noflip";
        this.setState({flip: flip});
    }

    login(){
        let logged = this.state.logged;
        this.setState({logged: !logged});
    }

    render() {
        let logged="";
        if(this.state.logged){
            logged="--logged";
        }
        let page = [<Menu login={() => this.login()} key="menu"/>,<Worksheet key="worksheet"/>];

        return (
            <div className={"page " + this.state.flip + " page" + logged}>
                {this.state.logged ?
                    page
                    :
                    <Auth flip={() => this.flip()} login={() => this.login()}/>
                }
            </div>
        );
    }
}

export default Page;