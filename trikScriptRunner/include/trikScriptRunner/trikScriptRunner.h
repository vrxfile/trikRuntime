#pragma once

/* Copyright 2014 CyberTech Labs Ltd.
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

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

namespace trikScriptRunner {

class ScriptRunnerProxy;

/// Executes scripts in Qt Scripting Engine.
class TrikScriptRunner : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	/// @param configFilePath - path to config file for trikControl, for example /home/root/trik/
	/// @param startDirPath - path to the directory from which the application was executed.
	TrikScriptRunner(QString const &configFilePath, QString const &startDirPath);

	~TrikScriptRunner();

	/// Executes given script asynchronously. If some script is already executing, it will be aborted.
	/// @param script - script in Qt Script language to be executed.
	void run(QString const &script);

	/// Reads a script from given file and asynchronously executes it. If some script is already executing, it will be
	/// aborted.
	/// @param fileName - name of a file with script.
	void runFromFile(QString const &fileName);

	/// Aborts script execution.
	void abort();

	/// Returns true if a system is in event-driven running mode, so it shall wait for events when script is executed.
	/// If it is false, script will exit immediately.
	bool isInEventDrivenMode() const;

signals:
	/// Fired when current script completes execution.
	void completed();

private slots:
	/// Called when script runner reports that it has finished execution. Used to stop robot.
	void onScriptExecutionCompleted();

private:
	enum State {
		idle
		, running
		, stopping
	};

	/// Proxy for script engine thread.
	QScopedPointer<ScriptRunnerProxy> mScriptRunnerProxy;

	/// Execution state of a runner.
	State mExecutionState;
};

}
