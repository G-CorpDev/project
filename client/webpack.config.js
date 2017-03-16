var webpack = require("webpack");

module.exports = {
    entry: {
        main: ['./src/scripts/main.js']
    }
    ,output: {
        filename: './dist/scripts/[name].js'
    }
    ,module: {
        loaders: [
            {
                test: /\.scss$/,
                exclude: /node_modules/,
                use: [{
                    loader: "style-loader"
                }, {
                    loader: "css-loader"
                }, {
                    loader: "sass-loader",
                    options: {
                        includePaths: []
                    }
                }]
            }
            ,{
                test: /\.js$/,
                exclude: /node_modules/,
                loaders: ['babel-loader'],
            }
            
        ]
    }
};