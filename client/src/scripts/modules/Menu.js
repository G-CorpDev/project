import React, {Component} from 'react';
import ReactDOM from 'react-dom';

class Menu extends Component {
    constructor(props) {
        super(props);
        this.state = {
            logout: props.logout,
            select: props.select,
            selected: "Select new worksheet",
            scrolled: "menu--notScrolled",
            nick: props.nick,
        };
        this.handleScroll = this.handleScroll.bind(this);
    }

    handleScroll() {
        let scrollTop = (window.pageYOffset !== undefined) ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
        if(scrollTop>=100){
            this.setState({scrolled:"menu--scrolled"});
        } else {
            this.setState({scrolled:"menu--notScrolled"});
        }
    }

    componentDidMount() {
        window.addEventListener('scroll', this.handleScroll);
    }

    componentWillUnmount() {
        window.removeEventListener('scroll', this.handleScroll);
    }

    select(menuItem) {
        this.setState({selected: menuItem});
        this.state.select(menuItem);
    }

    renderMenuItem(name, index) {
        let selected = this.state.selected === name ? "menu__item--selected" : "";
        return (
            <a className={"menu__item " + selected} onClick={() => this.select(name)} key={index}>{name}</a>
        )
    }

    render() {
        let _this = this;
        let menuTexts = ["My worksheet", "Select new worksheet"];
        let menuItems = [];
        menuTexts.forEach(function (element, index) {
            menuItems.push(_this.renderMenuItem(element, index));
        });

        return (
            <div className={"menu " + this.state.scrolled}>
                {menuItems}
                <a className="menu__item" onClick={() => this.state.logout()}>Logout</a>
                <div className="menu__hi">Hi, {this.state.nick}!</div>
            </div>
        );
    }
}

/*
 Body mass index calculator
 Calorie calculator
 */
export default Menu;