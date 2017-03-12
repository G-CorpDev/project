var path = require("path");
var webpack = require("webpack")

module.exports = {
  entry: './src/entry.js',
  output: {
    path: __dirname + '/build',
    publicPath: "/build/",
    filename: 'bundle.js'
  },
  module: {
      rules: [
          {
            test: /\.scss$/,
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
        },
        {
        test: /\.css$/,
        use: [ 'style-loader', 'css-loader' ]
        }
        ],
    loaders: [
      { test: /\.js$/, loader: 'babel-loader', exclude: /node_modules/ },
      { test: /\.jsx$/, loader: 'babel-loader', exclude: /node_modules/ },
      { test: /\.pug$/, loader: 'pug-loader', exclude: /node_modules/ },
      { test: /\.jade$/, loader: 'pug-loader', exclude: /node_modules/ },
    ]
  }
  ,node:{
      fs:'empty'
  }

  ,devServer: {
      port:3000
  }
}