# App.JS

## Introduction

App.JS is a simple javascript library for creating simple single page applications. The main focus is on mobile apps and overall lightweightness.

## Usage

The library is build to be fast and as tiny as possible. Because of that, it is provided uncompressed in the `src/` folder as app.js. You are supposed to put all of your scripts into `src/` as well and when you are finished (app is tested and ready to be deployed), use [https://jscompress.com/](https://jscompress.com/) where you can upload all of your files from the `src/` folder and compress them into a single `app.min.js`, which you then can link in the index.html.

## What is in the library

The library provides three basic objects: `ClassElement`, `ClassView` and `ClassApp`.

### App

`ClassApp` is an object holding all of the app data - it has reference to #Canvas dom, it has all of the persistent data stored in the context object and it has database of `ClassView`.

### View

`ClassView` is just a view/screen of your app. It can be screen with settings, with main UI, etc. Each view needs to have its own rendering method. You need to provide this rendering method and bind it to `ClassView::render` property. If you don't, the app will tell you. Each `ClassView` has reference to parent `ClassApp`, through `ClassView::app` property. The render method is basically where all of the magic happens.

### Element

Element is an object which has reference to some DOM and has properties width and height with values set in pixels. The `ClassApp::canvas` is the core `ClassElement` of the whole app and you have to start your render method from there. The `ClassElement` has three fundamental methods: `add`, `setColor` and `setText`. The `add` method allows you to add children nodes to the current `ClassElement`, `setColor` sets the background color and `setText` allows you to easily write text to the `ClassElement` that could scale to fit its container. If you need any other more advanced stuff, feel free to access `ClassElement::dom` property.

The common flow of work is following:

```
function Render() {
	var display = this.app.canvas.add(0, 0, 1, 0.9); // Create dom node taking 100% x 90% of the screen, positioned to topleft corner.
	display.setColor('lightgrey'); // Set lightgrey background
	display.setText('This is display', true); // true will ensure scale to fit. If your display is very very big, add a third argument with value of 1000. See docs for why.
	// RenderDisplay(display, this.app); // Draw other stuff to canvas
	
	var toolbar = this.app.canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	// RenderToolbar(toolbar, this.app);
}
```

As you can see from the following snippet, the add method accepts percentage values to allow for proper rensponsibility. This means that each time the viewport dimensions will change, the app will scale up/down properly as needed. The add method has even more quirks to it, check its documentation in `src/app.js`.

### Special keywords

App.JS, in conjunction with command line utility jsbloat (present in this repo) can be minified way more effectively than your usual javascript app. First off, if you need to use string based IDs in your app (many app.js methods do), wrap that string in call to ID: ID("MyUniqueID") at every occurence in code (do not store that string in variable).

Jsbloat will obfuscate those IDs and it will optimize away calls to ID, so your code will be smaller.

There is similar function called ENUM which will turn those strings into numbers.

Also, prepend each function definition with `'static';` statement. This will force obfuscation on those function calls. You can also use that for global variables and prototype functions as well.

I recommend to take result of jsbloat and use a production minified on that source since inter-functions minifications or whitespace and comment minifications are not tackled by jsbloat.

## Adding new files

Any .js source has to be added in appropriate head section in index.html.

## Production version

If you want to 