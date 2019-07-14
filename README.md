# Cutecloud

This prototype implementation aims to create a Nextcloud-like cloud solution using Cutelyst, Grantlee, Qt and C++.

# Goals

* small executable
* small RAM usage
* small CPU usage
* low latency
* (if possible) compatibility with Nextcloud ("drop in replacement")
* (if possible) compatibility with Nextcloud clients (desktop/ mobile)

# Thanks

* [Cutelyst](cutelyst.org) is used as base framework for this web page
* [Grantlee](https://github.com/steveire/grantlee) is used as templating engine
* [Qt](www.qt.io) is the C++ framework in which this project, Cutelys and Grantlee are all written

# Develop

## Qt Creator

Set build dir to `<root>/build`.

Set `Cutelyst2Qt5_DIR` to where `Cutelyst2Qt5Config.cmake` is located.

# Run

In `<root>`, run:

    cutelyst2 --server -p 3000 --app-file build/src/libcutecloud.so

Then open:

    localhost:3000

In any web browser.
