/**
  *   @file PhysicsGrid.hpp
  *   @author Lauri Westerholm
  *   @brief Header for class PhysicsGrid
  */

#pragma once

#include "../utils/Rect.hpp"
#include "../utils/Vector2.hpp"
#include "PhysicsObject.hpp"
#include "DynamicObject.hpp"
#include "StaticObject.hpp"
#include <list>
#include <map>


/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {


  /**
    *   @struct Cell
    *   @brief struct representing one cell in Grid
    */
  template<class T>
  struct Cell {
    std::list<T> entities; /**< list of entities Cell contains */
    bool active_cell; /**< Whether Cell is active or not */
  };

  /**
    *   @struct CompareRectMap
    *   @brief Used to hold comparison functions for std::map find
    */
  template<typename T>
  struct CompareRectMap {
    using is_transparent = void; /**< make template comparison overloads possible */

    /**
      *   @brief Standard comparison between Rects
      *   @param rect1 1st Rect to be compared
      *   @param rect2 2nd Rect to be compared
      *   @return rect1 < rect2
      */
    bool operator() (const Rect<T>& rect1, const Rect<T>& rect2) const {
      return rect1 < rect2;
    }

    /**
      *   @brief Position based comparison between Rect and Vector2
      *   @param pos Vector2 position
      *   @param rect Rect to be compared
      *   @return true if pos is smaller than rect left upper corner (min point)
      */
    bool operator() (const Vector2<T>& pos, const Rect<T>& rect) const {
      return (pos.getX() < rect.getPosition().getX()) && (pos.getY() < rect.getPosition().getY());
    }

    /**
      *   @brief Position based comparison between Rect and Vector2
      *   @param pos Vector2 position
      *   @param rect Rect to be compared
      *   @return true if pos is greater than rect right lower corner (max point)
      */
    bool operator() (const Rect<T>& rect, const Vector2<T>& pos) const {
      return (rect.getPosition().getX() + rect.getWidth() < pos.getX()) && (rect.getPosition().getY() + rect.getHeight() < pos.getY());
    }
  };

  /**
    *   @class PhysicsGrid
    *   @brief Container for PhysicsObject of PhysicsWorld
    *   @details Consists of Cell structs. PhysicsGrid and it's Cells take
    *   ownership of PhysicsObjects so their memory deletion is handled by Grid.
    *   Do NOT delete objects memory elsewhere
    */
    class PhysicsGrid
    {
      public:
        /**
          *   @brief Standard empty constructor
          */
        PhysicsGrid();

        /**
          *   @brief Deconstructor
          *   @details Frees all memory allocated by the Grid
          */
        virtual ~PhysicsGrid();

        /**
          *   @brief Copy constructor
          *   @param grid Grid which is copied
          */
        PhysicsGrid(const PhysicsGrid& grid);

        /**
          *   @brief Assignment operator overload
          *   @param grid Grid which is copied
          */
        PhysicsGrid& operator=(const PhysicsGrid& grid);

        /**
          *   @brief Add cell to Grid
          *   @details After Cell is added, Grid maintains removal of the entities
          *   and frees memory allocated for them
          *   @param position where cell is added on 2D plane
          */
        bool addCell(Recti position);

        /**
          *   @brief Add PhysicsObject to Cell in the Grid
          *   @param object to be added
          *   @return true if object was added, otherwise false
          *   @details object cannot be added if there is no Cell matching to
          *   the position of object
          *   @remark This is not very trustworthy, only the center of object
          *   is checked whether it's inside Cell or not
          */
        bool addObject(PhysicsObject* object);

      private:
        /**
          *   @brief Clear Grid
          *   @details Removes all cells and their objects. Deletes also memory used for
          *   those
          */
        void Clear();

        /**
          *   @brief Copy Grid
          *   @details Makes hard copy of the Grid, i.e. allocates new pointers for
          *   objects
          *   @param grid Grid to be copied
          */
        void Copy(const PhysicsGrid& grid);


        std::map<Recti, Cell<PhysicsObject*>*, CompareRectMap<int>> cells;
    };




} // end of namespace pe
