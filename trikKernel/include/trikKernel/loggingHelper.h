/* Copyright 2015 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QString>
#include <QtCore/QSharedPointer>

namespace QsLogging {
class Destination;
}

namespace trikKernel {

/// Helper for working with QsLog library.
class LoggingHelper
{
public:
	/// Constructor. Initializes logger with default settings, supposed to be alive until program finishes (RAII idiom).
	/// @param pathToLog - path to "trik.log" file that will be created or appended by logger. Supposed to end with "/".
	LoggingHelper(const QString &pathToLog);

	~LoggingHelper();

private:
	QSharedPointer<QsLogging::Destination> mFileDestination;
	QSharedPointer<QsLogging::Destination> mConsoleDestination;
};

}
