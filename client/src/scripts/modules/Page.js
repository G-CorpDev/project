import React, {Component} from 'react';

import Auth from './Auth.js';
import Content from './Content.js';

class Page extends Component {
    constructor(props) {
        super(props);
        this.state = {
            flip: "page--noflip",
            logged: true,
            loading: "",
            pers: " page--noPersp",
        }
    }

    flip() {
        let flip = this.state.flip === "page--noflip" ? "page--flip" : "page--noflip";
        this.setState({flip: flip});
    }

    login() {
        let _this = this;
        this.setState({loading: " page--loading"}, function () {
            setTimeout(function () {
                let logged = _this.state.logged;
                let pers = !logged ? " page--noPersp" : " page--Persp";
                _this.setState({logged: !logged, loading: "", pers: pers});
            }, 800);
        });
    }

    render() {

        return (
            <div className={"page " + this.state.flip + this.state.loading + this.state.pers}>
                {this.state.logged ?
                    <Content login={() => this.login()}/>
                    :
                    <Auth flip={() => this.flip()} login={() => this.login()}/>
                }
            </div>
        );
    }
}

export default Page;