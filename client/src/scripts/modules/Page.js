import React, {Component} from 'react';

import Auth from './Auth.js';
import Content from './Content.js';

class Page extends Component {
    constructor(props) {
        super(props);
        this.state = {
            flip: "page--noflip",
            logged: false,
            loading: "",
            pers: " page--Persp",
            userId : "",
            userNick: "",
        }
    }

    flip() {
        let flip = this.state.flip === "page--noflip" ? "page--flip" : "page--noflip";
        this.setState({flip: flip});
    }

    login(id,nick) {
        let _this = this;
        this.setState({loading: " page--loading"}, function () {
            setTimeout(function () {
                _this.setState({logged: true, loading: "", pers: " page--noPersp", userId: id, userNick: nick});
            }, 800);
        });
    }

    logout() {
        let _this = this;
        this.setState({loading: " page--loading"}, function () {
            setTimeout(function () {
                _this.setState({logged: false, loading: "", pers: " page--Persp", userId: "", userNick: ""});
            }, 800);
        });
    }

    render() {

        return (
            <div className={"page " + this.state.flip + this.state.loading + this.state.pers}>
                {this.state.logged ?
                    <Content logout={() => this.logout()} nick={this.state.userNick}/>
                    :
                    <Auth flip={() => this.flip()} login={(i,n) => this.login(i,n)}/>
                }
            </div>
        );
    }
}

export default Page;