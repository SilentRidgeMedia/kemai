# Archived
While this initially was a good idea, it turned out there are other tools that suited our needs better.
This was the work of our junior collegaue where he got an assignment to add feature for adding support for multiple servers and
contains ui and some code in order to get it to work, which it, at atleast one time, did. 
However code in current state is likley not usable at all. Use as you wish but let us know at info @ silentridge.io if you ever can get any use if it.

# Kemai, a Kimai Desktop Client

## Build Status

|Develop|Master|Translation|
|:--:|:--:|:--:|
|![Build status](https://ci.appveyor.com/api/projects/status/github/AlexandrePTJ/Kemai?branch=develop&svg=true)|![Build status](https://ci.appveyor.com/api/projects/status/github/AlexandrePTJ/Kemai?branch=master&svg=true)|[![Translation status](https://hosted.weblate.org/widgets/kemai/-/kemai/svg-badge.svg)](https://hosted.weblate.org/engage/kemai/)|

## How to use

_Kemai_ connect to your _Kimai_ instance through its API. As credentials for API are not the same as login, here is how
to create them:

![API password](https://github.com/AlexandrePTJ/kemai/blob/master/docs/api_password.gif)

Then, you can set this credentials to _Kemai_ settings :

![Kemai settings](https://github.com/AlexandrePTJ/kemai/blob/master/docs/kemai_settings.gif)

## How to build

_Kemai_ is Qt5 based application and it uses CMake to build. So regular cmake process will work.

```shell script
> cmake . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<path to Qt installation>
> cmake --build build --config Release
```

## How to help

Ideas, pull requests and translation are welcome.

For the later, [Weblate](https://hosted.weblate.org/engage/kemai/) is used. Here is the current status:

[![Translation status](https://hosted.weblate.org/widgets/kemai/-/kemai/multi-auto.svg)](https://hosted.weblate.org/engage/kemai/)

## Why Kemai

Because "Il n'y a que Maille qui m'aille".
