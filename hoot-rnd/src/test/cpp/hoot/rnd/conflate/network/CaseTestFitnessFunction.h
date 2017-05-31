/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2015, 2017 DigitalGlobe (http://www.digitalglobe.com/)
 */

#ifndef __CASETESTFITNESSFUNCTION_H__
#define __CASETESTFITNESSFUNCTION_H__

// Cpp Unit
#include <cppunit/TestResult.h>

// Hoot
#include <hoot/core/test/ConflateCaseTestSuite.h>
#include <hoot/core/util/Log.h>

// Qt
#include <QTemporaryFile>

// Tgs
#include <tgs/Optimization/FitnessFunction.h>
#include <tgs/Optimization/State.h>

namespace hoot
{

/**
 * Fitness function which optimizes against Hootenanny conflate case test data
 */
class CaseTestFitnessFunction : public Tgs::FitnessFunction
{

public:

    CaseTestFitnessFunction();

    virtual double f(const Tgs::ConstStatePtr& s);

    int getTestCount() { return _testCount; }

    QStringList getFailingTestsForBestRuns() { return _failingTestsForBestRuns; }

private:

    int _testCount;
    int _lowestNumFailingTestsPerRun;
    //list members are one or more test names joined by a ';'
    QStringList _failingTestsForBestRuns;
    boost::shared_ptr<ConflateCaseTestSuite> _testSuite;

    QString _failedTestsToString(const QStringList failedTests) const;
};

}

#endif // __CASETESTFITNESSFUNCTION_H__
