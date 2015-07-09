/*
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef QHTTPENGINE_QHTTPHANDLER_H
#define QHTTPENGINE_QHTTPHANDLER_H

#include <QObject>

#include "qhttpengine.h"
#include "qhttpsocket.h"

class QHTTPENGINE_EXPORT QHttpHandlerPrivate;

/**
 * @brief Base class for URL handlers
 * @headerfile qhttphandler.h QHttpHandler
 *
 * When a request is received by a QHttpServer, it is dispatched to a
 * QHttpHandler instance which will then determine what happens to the
 * request. This is done by reimplementing the process() method.
 *
 * This method is invoked either by a QHttpServer or a QSubHandler and is
 * passed two arguments:
 *
 * \li the socket (request headers already parsed)
 * \li the relative request path (leading slash removed)
 *
 * For example, if a QHttpServer is initialized with a QFilesystemHandler, the
 * process() method will be invoked each time a request comes in and the path
 * will be set to QHttpSocket::path() (with the leading slash removed).
 *
 * [...]
 */
class QHTTPENGINE_EXPORT QHttpHandler : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Base constructor for a handler
     *
     * Because this class is abstract, it cannot be instantiated.
     */
    explicit QHttpHandler(QObject *parent = 0);

    /**
     * @brief Add a handler for a specific pattern
     *
     * The pattern and handler will be added to an internal list that will be
     * used when the process() method is invoked to determine whether the
     * request matches any patterns. Order is preserved.
     */
    void addSubHandler(const QRegExp &pattern, QHttpHandler *handler);

    /**
     * @brief [...]
     */
    void route(QHttpSocket *socket, const QString &path);

protected:

    /**
     * @brief Attempt to process a request
     *
     * This method should process the request either by fulfilling it or
     * writing an error to the socket using QHttpSocket::writeError().
     *
     * Note that the leading "/" will be stripped from the path.
     */
    virtual void process(QHttpSocket *socket, const QString &path);

private:

    QHttpHandlerPrivate *const d;
};

#endif // QHTTPENGINE_QHTTPHANDLER_H
