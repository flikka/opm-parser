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

#ifndef GROUPTREENODE_HPP
#define	GROUPTREENODE_HPP

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

namespace Opm {

    /// This Class is currently ONLY keeping track of the actual group nodes, 
    /// and knows nothing about the wells. The wells will know which group 
    /// (leaf) node they belong to. 
    class GroupTreeNode {
    public:
        const std::string& name() const;
        GroupTreeNode * parent() const;
        boost::shared_ptr<GroupTreeNode> addChildGroup(const std::string& childName);
        bool hasChildGroup(const std::string& childName) const;
        boost::shared_ptr<GroupTreeNode> getChildGroup(const std::string& childName);

        void setParent(GroupTreeNode * parent);
        static boost::shared_ptr<GroupTreeNode> createFieldNode();
        std::map<std::string, boost::shared_ptr<GroupTreeNode> >::iterator begin();
        std::map<std::string, boost::shared_ptr<GroupTreeNode> >::iterator end();

        
    private:
        GroupTreeNode(const std::string& name);
        GroupTreeNode(const std::string& name, GroupTreeNode * parent);
        std::string m_name;
        std::map<std::string, boost::shared_ptr<GroupTreeNode> > m_childGroups; 
        GroupTreeNode * m_parent;
    };

    typedef boost::shared_ptr<GroupTreeNode> GroupTreeNodePtr;
    typedef boost::shared_ptr<const GroupTreeNode> GroupTreeNodeConstPtr;
}

#endif	/* GROUPTREENODE_HPP */
