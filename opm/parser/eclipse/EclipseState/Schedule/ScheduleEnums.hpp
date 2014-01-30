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

#ifndef SCHEDULE_ENUMS_H
#define SCHEDULE_ENUMS_H

#include <string>
#include <stdexcept>

namespace Opm {
    namespace WellCommon {

        enum StatusEnum {
            OPEN = 1,
            STOP = 2,
            SHUT = 3, 
            AUTO = 4 
        };

        const std::string Status2String(StatusEnum enumValue);
        StatusEnum StatusFromString(const std::string& stringValue);
    }


    enum CompletionStateEnum {
        OPEN = 1,
        SHUT = 2,
        AUTO = 3
    };


    namespace Phase { 
        enum PhaseEnum {
            OIL   = 1,
            GAS   = 2,
            WATER = 4
        };

        const std::string PhaseEnum2String( PhaseEnum enumValue );
        PhaseEnum PhaseEnumFromString( const std::string& stringValue );
    };



    namespace WellInjector {
        enum TypeEnum {
            WATER = 1,
            GAS = 2,
            OIL = 3,
            MULTI = 4
        };

        
        enum ControlModeEnum {
            RATE = 1,
            RESV = 2 , 
            BHP = 3,
            THP = 4,
            GRUP = 5
        };


        const std::string ControlMode2String( ControlModeEnum enumValue );
        ControlModeEnum ControlModeFromString( const std::string& stringValue );

        const std::string Type2String( TypeEnum enumValue );
        TypeEnum TypeFromString( const std::string& stringValue );
    };

    
    namespace GroupInjection {
        
          enum ControlEnum {
            NONE = 0,
            RATE = 1,
            RESV = 2,
            REIN = 3,
            VREP = 4,
            FLD  = 5
        };

        const std::string ControlEnum2String( ControlEnum enumValue );
        ControlEnum ControlEnumFromString( const std::string& stringValue );
    }

    
    namespace GroupProductionExceedLimit {
        enum ActionEnum {
            NONE = 0,
            CON = 1,
            CON_PLUS = 2,   // String: "+CON"
            WELL = 3,
            PLUG = 4,
            RATE = 5
        };
            
        const std::string ActionEnum2String( ActionEnum enumValue );
        ActionEnum ActionEnumFromString( const std::string& stringValue );
    }
    
    

    namespace GroupProduction {

        enum ControlEnum {
            NONE = 0,
            ORAT = 1,
            WRAT = 2,
            GRAT = 3,
            LRAT = 4,
            CRAT = 5,
            RESV = 6,
            PRBL = 7
        };
        
        const std::string ControlEnum2String( GroupProduction::ControlEnum enumValue );
        GroupProduction::ControlEnum ControlEnumFromString( const std::string& stringValue );    
    }


    const std::string CompletionStateEnum2String( CompletionStateEnum enumValue );
    CompletionStateEnum CompletionStateEnumFromString( const std::string& stringValue );

    
}

#endif
