# BuildBot Status
##About

The Idea to this App came from my wish to get an easy overview over the status of the builds being run on my [Buildbot](http://buildbot.net) server on my BlackBerry Device.

As I always wanted to start learning how to write BlackBerry Apps and I came home after drinking some beer it seemed the perfect starting point to do so, as the main concepts behind it seemed pretty simple.

* Get a first look into the native Cascades Framework with C++, Qt and QML
* Design a simple GUI
* Issue a simple GET request to the servers JSON API
* Parse the builders names out of the response
* Issue another GET request for each builder to get its status
* Parse the builders status out of the response
* Display a list of builders with their status
* Additionally support for HTTP basic auth would be nice as my server is protected

So I took another beer and started coding. After a second evening and several beers later I got a working app that gives no useful response on errors, used the architecture pattern "terrible mess" and consists of the given pieces of terrible spaghetti-code that consequently ignores any conventions for clean code, error handling and all that stuff.

Later I took a further look into it and frowned, deciding to release this as an example how not to do it. When I've got some spare time I'll first gonna start by rewriting / refactoring it and then possibly to implement further features (starting with the still uninplemented HTTP basic auth).

Possibly I'll also write something about this App or related stuff on my [Blog](http://pzzz.de/category/buildbot-status/).

## Current status / Roadmap
As stated below since yet not even my requested features are implemented. Therefore I'll give a fine-grained view on what is implemented and what is upcoming.

Implemented:

- [x] GUI for inputting server address, enabling HTTPS, enabling HTTP basic auth and HTTP basic auth user and password
- [x] GUI for displaying a list of builders and their status (still a little ugly)

Implemented but really unstructured and messed up code:

- [x] Method to connect to the specified server
- [x] Option to use HTTPS connection
- [x] Method to request a list of builders (/json/builders)
- [x] Method to extract the builders from the JSON response
- [x] Method to get the latest build results from each builder (/json/builders/<builder name>/builds/-1)
- [x] Method to extract the build status from the JSON response

Not implemented:

- [ ] Automated Tests
- [ ] Error handling
- [ ] Option to use HTTP basic auth

Further Ideas:

- [ ] Add support for saving the configuration
- [ ] Add support for saving multiple servers
- [ ] Use more parts of the API to display more detailled Information
- [ ] Add support for running headless and pulling at given time intervals

## Screenshots
Here you see some Screenshots taken on my BlackBerry Q10 with OS 10.3.1:

* Settings page
![Screenshot of the settings page](https://raw.githubusercontent.com/pzzz/BuildBotStatus/master/screenshots/settings_q10.png)
* Results page
![Screenshot of the results page](https://raw.githubusercontent.com/pzzz/BuildBotStatus/master/screenshots/results_q10.png)

## License
Currently I did choose the free MIT license, but I must admit that I simply only chose a license because  github forced me to choose a license when creating this repo. I might think about that in future and change the license.

### Warning
Any way I do not see the code I do release here as software but as educational sample how not to do it.

Therefore in addition to the given license I want to explicitly warn from all kinds of unintended effects that may happen when you try to execute the code. This could reach from working as expected over crashing your device to deleting the whole internet.
