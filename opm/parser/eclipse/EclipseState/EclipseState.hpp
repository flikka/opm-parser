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

#ifndef OPM_ECLIPSE_STATE_HPP
#define OPM_ECLIPSE_STATE_HPP

#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/OpmLog/OpmLog.hpp>

#include <opm/parser/eclipse/EclipseState/Schedule/Schedule.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/EclipseGrid.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/Box.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/BoxManager.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/GridProperties.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/TransMult.hpp>
#include <opm/parser/eclipse/EclipseState/Schedule/ScheduleEnums.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/FaultCollection.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/NNC.hpp>

#include <opm/parser/eclipse/EclipseState/Tables/TableManager.hpp>
#include <opm/parser/eclipse/EclipseState/InitConfig/InitConfig.hpp>
#include <opm/parser/eclipse/EclipseState/SimulationConfig/SimulationConfig.hpp>
#include <opm/parser/eclipse/EclipseState/IOConfig/IOConfig.hpp>

#include <opm/parser/eclipse/Parser/ParseMode.hpp>

#include <set>
#include <memory>
#include <iostream>
#include <map>
#include <vector>

namespace Opm {
    class EclipseState {
    public:
        enum EnabledTypes {
            IntProperties = 0x01,
            DoubleProperties = 0x02,

            AllProperties = IntProperties | DoubleProperties
        };

        EclipseState(DeckConstPtr deck , const ParseMode& parseMode);

        const ParseMode& getParseMode() const;
        ScheduleConstPtr getSchedule() const;
        IOConfigConstPtr getIOConfigConst() const;
        IOConfigPtr getIOConfig() const;
        InitConfigConstPtr getInitConfig() const;
        SimulationConfigConstPtr getSimulationConfig() const;
        EclipseGridConstPtr getEclipseGrid() const;
        EclipseGridPtr getEclipseGridCopy() const;
        bool hasPhase(enum Phase::PhaseEnum phase) const;
        std::string getTitle() const;
        bool supportsGridProperty(const std::string& keyword, int enabledTypes=AllProperties) const;

        std::shared_ptr<GridProperty<int> > getRegion(DeckItemConstPtr regionItem) const;
        std::shared_ptr<GridProperty<int> > getDefaultRegion() const;
        std::shared_ptr<GridProperty<int> > getIntGridProperty( const std::string& keyword ) const;
        std::shared_ptr<GridProperty<double> > getDoubleGridProperty( const std::string& keyword ) const;
        bool hasIntGridProperty(const std::string& keyword) const;
        bool hasDoubleGridProperty(const std::string& keyword) const;

        void loadGridPropertyFromDeckKeyword(std::shared_ptr<const Box> inputBox,
                                             DeckKeywordConstPtr deckKeyword,
                                             int enabledTypes = AllProperties);

        std::shared_ptr<const FaultCollection> getFaults() const;
        std::shared_ptr<const TransMult> getTransMult() const;
        std::shared_ptr<const NNC> getNNC() const;
        bool hasNNC() const;

        std::shared_ptr<const TableManager> getTableManager() const;
        size_t getNumPhases() const;

        // the unit system used by the deck. note that it is rarely needed to convert
        // units because internally to opm-parser everything is represented by SI
        // units...
        std::shared_ptr<const UnitSystem> getDeckUnitSystem()  const;
        void applyModifierDeck( std::shared_ptr<const Deck> deck);

    private:
        void initTabdims(DeckConstPtr deck);
        void initTables(DeckConstPtr deck);
        void initIOConfig(DeckConstPtr deck);
        void initSchedule(DeckConstPtr deck);
        void initIOConfigPostSchedule(DeckConstPtr deck);
        void initInitConfig(DeckConstPtr deck);
        void initSimulationConfig(DeckConstPtr deck);
        void initEclipseGrid(DeckConstPtr deck);
        void initGridopts(DeckConstPtr deck);
        void initPhases(DeckConstPtr deck);
        void initTitle(DeckConstPtr deck);
        void initProperties(DeckConstPtr deck);
        void initTransMult();
        void initFaults(DeckConstPtr deck);
        void initNNC(DeckConstPtr deck);


        void setMULTFLT(std::shared_ptr<const Section> section) const;
        void initMULTREGT(DeckConstPtr deck);

        double getSIScaling(const std::string &dimensionString) const;

        void processGridProperties(Opm::DeckConstPtr deck, int enabledTypes);
        void scanSection(std::shared_ptr<Opm::Section> section , int enabledTypes);
        void handleADDKeyword(DeckKeywordConstPtr deckKeyword  , BoxManager& boxManager, int enabledTypes);
        void handleBOXKeyword(DeckKeywordConstPtr deckKeyword  , BoxManager& boxManager);
        void handleCOPYKeyword(DeckKeywordConstPtr deckKeyword , BoxManager& boxManager, int enabledTypes);
        void handleENDBOXKeyword(BoxManager& boxManager);
        void handleEQUALSKeyword(DeckKeywordConstPtr deckKeyword   , BoxManager& boxManager, int enabledTypes);
        void handleMULTIPLYKeyword(DeckKeywordConstPtr deckKeyword , BoxManager& boxManager, int enabledTypes);

        void handleEQUALREGKeyword(DeckKeywordConstPtr deckKeyword, int enabledTypes);
        void handleMULTIREGKeyword(DeckKeywordConstPtr deckKeyword, int enabledTypes);
        void handleADDREGKeyword(DeckKeywordConstPtr deckKeyword  , int enabledTypes);
        void handleCOPYREGKeyword(DeckKeywordConstPtr deckKeyword , int enabledTypes);

        void setKeywordBox(DeckKeywordConstPtr deckKeyword, size_t recordIdx, BoxManager& boxManager);

        void copyIntKeyword(const std::string& srcField , const std::string& targetField , std::shared_ptr<const Box> inputBox);
        void copyDoubleKeyword(const std::string& srcField , const std::string& targetField , std::shared_ptr<const Box> inputBox);

        void complainAboutAmbiguousKeyword(DeckConstPtr deck, const std::string& keywordName) const;

        EclipseGridConstPtr      m_eclipseGrid;
        IOConfigPtr              m_ioConfig;
        InitConfigConstPtr       m_initConfig;
        ScheduleConstPtr         schedule;
        SimulationConfigConstPtr m_simulationConfig;

        std::shared_ptr<const TableManager> m_tables;

        std::set<enum Phase::PhaseEnum> phases;
        std::string m_title;
        std::shared_ptr<const UnitSystem> m_deckUnitSystem;
        std::shared_ptr<GridProperties<int> > m_intGridProperties;
        std::shared_ptr<GridProperties<double> > m_doubleGridProperties;
        std::shared_ptr<TransMult> m_transMult;
        std::shared_ptr<FaultCollection> m_faults;
        std::shared_ptr<NNC> m_nnc;
        std::string m_defaultRegion;
        const ParseMode& m_parseMode;
    };

    typedef std::shared_ptr<EclipseState> EclipseStatePtr;
    typedef std::shared_ptr<const EclipseState> EclipseStateConstPtr;
}

#endif
