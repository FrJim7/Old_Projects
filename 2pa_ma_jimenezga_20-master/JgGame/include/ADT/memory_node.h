/**
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */

#ifndef __MEMORY_NODE_H__
#define __MEMORY_NODE_H__ 1

#include "adt_def.h"

/**
 * @brief      MemoryNode class
 *
 *             Basic data storage for adt library.
 */
class MemoryNode {
 public:

  /**
   * @brief      Default Constructor
   *
   *             Initialize the data pointer and size to default values.
   */
  MemoryNode();

  /**
   * @brief      Copy Constructor
   *
   *             Initialize the data pointer and size to the values of other
   *             MemoryNode.
   *
   * @param[in]  other  MemoryNode reference to initialize.
   */
  MemoryNode(const MemoryNode &other);
 
  /**
   * @brief      Default Destructor
   *
   *             Frees the data if exist.
   */
 ~MemoryNode();
  
  /**
   * @brief      Resets the MemoryNode data.
   *
   *             Resets the data of the MemoryNode.
   *
   * @param      node  The MemoryNode to reset.
   *
   * @return     { Error if node = nullptr, OK otherwise }
   */
  s16 reset();

  /**
   * @brief      Sets the data in the MemoryNode.
   *
   *             Set the data pointer to the data passed by parameter, from now
   *             on the data passed cant be used.
   *
   * @param      data  The data to store.
   *
   * @return     { Error if node = nullptr or data = nullptr, OK otherwise }
   */
  s16 set_data(void *data);

  /**
   * @brief      Returns data.
   *
   * @return     { Data stored by the MemoryNode }
   */
  void* data();

 private:
  void *data_;
};

#endif//__MEMORY_NODE_H__