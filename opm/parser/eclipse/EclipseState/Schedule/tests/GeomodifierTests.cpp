/*
  Copyright 2013 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdexcept>
#include <iostream>
#include <boost/filesystem.hpp>
#define BOOST_TEST_MODULE GeoModifiersTests
#include <boost/test/unit_test.hpp>


#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParserKeywords.hpp>
#include <opm/parser/eclipse/Parser/InputErrorAction.hpp>
#include <opm/parser/eclipse/Parser/ParseMode.hpp>

#include <opm/parser/eclipse/EclipseState/Grid/EclipseGrid.hpp>
#include <opm/parser/eclipse/EclipseState/Schedule/Schedule.hpp>
#include <opm/parser/eclipse/EclipseState/IOConfig/IOConfig.hpp>

using namespace Opm;


BOOST_AUTO_TEST_CASE( CheckUnsoppertedInSCHEDULE ) {
    const char * deckString =
        "START\n"
        " 10 'JAN' 2000 /\n"
        "RUNSPEC\n"
        "DIMENS\n"
        "  10 10 10 / \n"
        "SCHEDULE\n"
        "TSTEP -- 1,2\n"
        "   10 10/\n"
        "MULTFLT\n"
        "   'F1' 100 /\n"
        "/\n"
        "TSTEP  -- 3,4\n"
        "   10 10/\n"
        "\n";

    ParseMode parseMode;
    Parser parser(true);

    auto deck = parser.parseString( deckString , parseMode );
    std::shared_ptr<EclipseGrid> grid = std::make_shared<EclipseGrid>( deck );
    std::shared_ptr<IOConfig> ioconfig = std::make_shared<IOConfig>( "path" );

    parseMode.update( ParseMode::UNSUPPORTED_SCHEDULE_GEO_MODIFIER , InputError::IGNORE );
    {
        Schedule schedule( parseMode , grid , deck , ioconfig );
        auto events = schedule.getEvents( );
        BOOST_CHECK_EQUAL( false , events.hasEvent( ScheduleEvents::GEO_MODIFIER , 1 ));
        BOOST_CHECK_EQUAL( true  , events.hasEvent( ScheduleEvents::GEO_MODIFIER , 2 ));
        BOOST_CHECK_EQUAL( false , events.hasEvent( ScheduleEvents::GEO_MODIFIER , 3 ));
    }
}
