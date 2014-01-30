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

#include <opm/parser/eclipse/EclipseState/Schedule/Completion.hpp>
#include <opm/parser/eclipse/EclipseState/Schedule/ScheduleEnums.hpp>

namespace Opm {

    Completion::Completion(int i, int j , int k , CompletionStateEnum state , double CF, double diameter, double skinFactor) {
        m_i = i;
        m_j = j;
        m_k = k;

        m_state = state;
        m_CF = CF;
        m_diameter = diameter;
        m_skinFactor = skinFactor;
    }


    bool Completion::sameCoordinate(const Completion& other) const {
        if ((m_i == other.m_i) && 
            (m_j == other.m_j) && 
            (m_k == other.m_k))
            return true;
        else
            return false;
    }


    int Completion::getI() const {
        return m_i;
    }

    int Completion::getJ() const {
        return m_j;
    }

    int Completion::getK() const {
        return m_k;
    }

    CompletionStateEnum Completion::getState() const {
        return m_state;
    }

    double Completion::getCF() const {
        return m_CF;
    }

    double Completion::getDiameter() const {
        return m_diameter;
    }
    
    double Completion::getSkinFactor() const {
        return m_skinFactor;
    }
}


