/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the StationManager class that is a subclass of LinkedList that stores KitchenStation* objects, which represents a station manager in a virtual bistro simulation.
 * 
 * The StationManager class includes a default constructor, destructor, and methods to manage and present the details of the station manager. 
 * 
 * @date December 1, 2024
 * @author Kun Feng Wei
 */

#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

/**
 * Retrieves the current dish preparation queue.
 * @return A copy of the queue containing pointers to Dish objects.
 * @post: The dish preparation queue is returned unchanged.
 */
std::queue<Dish*> StationManager::getDishQueue() const
{
    return dish_queue_;
}

/**
 * Retrieves the list of backup ingredients.
 * @return A vector containing Ingredient objects representing backup
supplies.
 * @post: The list of backup ingredients is returned unchanged.
 */
std::vector<Ingredient> StationManager::getBackupIngredients() const
{
    return backup_ingredients_;
}

/**
 * Sets the current dish preparation queue.
 * @param dish_queue A queue containing pointers to Dish objects.
 * @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
 * @post: The dish preparation queue is replaced with the provided
queue. */
void StationManager::setDishQueue(std::queue<Dish*> dish_queue)
{
    dish_queue_ = dish_queue;
}

// Method	Definition
// queue::empty()	Returns whether the queue is empty. It return true if the queue is empty otherwise returns false.
// queue::size()	Returns the size of the queue.
// queue::swap()	Exchange the contents of two queues but the queues must be of the same data type, although sizes may differ.
// queue::emplace()	Insert a new element into the queue container, the new element is added to the end of the queue.
// queue::front()	Returns a reference to the first element of the queue.
// queue::back()	Returns a reference to the last element of the queue.
// queue::push(g) 	Adds the element ‘g’ at the end of the queue.
// queue::pop() 	Deletes the first element of the queue.

/**
 * Adds a dish to the preparation queue without dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @pre: The dish pointer is not null.
 * @post: The dish is added to the end of the queue.
 */
void StationManager::addDishToQueue(Dish* dish)
{
    if (dish != nullptr)
    {
        dish_queue_.push(dish);
    }
}

/**
 * Adds a dish to the preparation queue with dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @param request A DietaryRequest object specifying dietary
accommodations.
 * @pre: The dish pointer is not null.
 * @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
 */
void StationManager::addDishToQueue(Dish* dish, const Dish::DietaryRequest& request)
{
    if (dish != nullptr)
    {
        dish->dietaryAccommodations(request);
        dish_queue_.push(dish);
    }
}

/**
 * Prepares the next dish in the queue if possible.
 * @pre: The dish queue is not empty.
 * @post: The dish is processed and removed from the queue.
 * If the dish cannot be prepared, it stays in the queue
 * @return: True if the dish was prepared successfully; false otherwise.
 */
bool StationManager::prepareNextDish()
{
    if (dish_queue_.empty() == true)
    {
        return false;
    }

    Dish* dish = dish_queue_.front();
    dish_queue_.pop();

    for (size_t i = 0; i < getLength(); i++)
    {
        KitchenStation* station = getEntry(i);
        if (station->canCompleteOrder(dish->getName()) && station->prepareDish(dish->getName()))
        {
            return true;
        }
    }
    dish_queue_.push(dish);
    return false;
}  

/**
 * Displays all dishes in the preparation queue.
* @pre: None.
 * @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/
void StationManager::displayDishQueue()
{
    std::queue<Dish*> temp_dish_queue_ = dish_queue_;
    while (temp_dish_queue_.empty() == false)
    {
        Dish* temp_dish = temp_dish_queue_.front();
        std::cout << temp_dish->getName() << std::endl;
        temp_dish_queue_.pop(); 
    }
}

/**
 * Clears all dishes from the preparation queue.
 * @pre: None.
 * @post: The dish queue is emptied and all allocated memory is freed.
 */
void StationManager::clearDishQueue()
{
    while (dish_queue_.empty() == false)
    {
        Dish* dish = dish_queue_.front();
        delete dish;        
        dish_queue_.pop();
    }
}

/**
 * Replenishes a specific ingredient at a given station from the backup
ingredients stock by a specified quantity.
 * @param station_name A string representing the name of the station.
 * @param ingredient_name A string representing the name of the ingredient
to replenish.
 * @param quantity An integer representing the amount to replenish.
 * @pre None.
 * @post If the ingredient is found in the backup ingredients stock and has
sufficient quantity, it is added to the station's ingredient stock by the
specified amount, and the function returns true.
 *       The quantity of the ingredient in the backup stock is decreased by
the specified amount.
 *       If the ingredient in backup stock is depleted (quantity becomes
zero), it is removed from the backup stock.
 *       If the ingredient does not have sufficient quantity in backup
stock, or the ingredient or station is not found, returns false.
* @return True if the ingredient was replenished from backup; false
otherwise.
 */
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, const int& quantity)
{
    KitchenStation* station = findStation(station_name);
    if (station == nullptr)
    {
        return false;
    }

    for (size_t i = 0; i < backup_ingredients_.size(); i++)
    {
        if (backup_ingredients_[i].name == ingredient_name && backup_ingredients_[i].quantity >= quantity)
        {
            if (replenishIngredientAtStation(station_name, Ingredient{ingredient_name, quantity, {}, {}}))
            {
                backup_ingredients_[i].quantity = backup_ingredients_[i].quantity - quantity;

                if (backup_ingredients_[i].quantity <= 0)
                {
                    backup_ingredients_.erase(backup_ingredients_.begin() + i);
                    i--;
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

/**
 * Sets the backup ingredients stock with the provided list of ingredients.
 * @param ingredients A vector of Ingredient objects to set as the backup
stock.
 * @pre None.
 * @post The backup_ingredients_ vector is replaced with the provided
ingredients.
 * @return True if the ingredients were added; false otherwise.
 */
bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients)
{
    backup_ingredients_ = ingredients;
    return true;
}

/**
 * Adds a single ingredient to the backup ingredients stock.
 * @param ingredient An Ingredient object to add to the backup stock.
 * @pre None.
 * @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
 *       If the ingredient does not exist, it is added to the backup stock.
 * @return True if the ingredient was added; false otherwise.
 */
bool StationManager::addBackupIngredient(const Ingredient& ingredient)
{
    for (size_t i = 0; i < backup_ingredients_.size(); i++)
    {
        if (backup_ingredients_[i].name == ingredient.name)
        {
            backup_ingredients_[i].quantity = backup_ingredients_[i].quantity + ingredient.quantity;
            return true;
        }
    }
    backup_ingredients_.push_back(ingredient);
    return true;
}

/**
 * Empties the backup ingredients vector
 * @post The backup_ingredients_ private member variable is empty.
 */
void StationManager::clearBackupIngredients()
{
    backup_ingredients_.clear();
}

// PREPARING DISH: Spaghetti Bolognese
// Pasta Station attempting to prepare Spaghetti Bolognese...
// Pasta Station: Insufficient ingredients. Replenishing ingredients...
// Pasta Station: Ingredients replenished.
// Pasta Station: Successfully prepared Spaghetti Bolognese.
// All dishes have been processed.

// PREPARING DISH: Vegan Salad
// Salad Station attempting to prepare Vegan Salad...
// Salad Station: Successfully prepared Vegan Salad.
// All dishes have been processed.

// PREPARING DISH: Seafood Paella
// Seafood Station attempting to prepare Seafood Paella...
// Seafood Station: Insufficient ingredients. Replenishing ingredients...
// Seafood Station: Unable to replenish ingredients. Failed to prepare Seafood Paella.
// Seafood Paella was not prepared.
// All dishes have been processed.

// PREPARING DISH: Grilled Chicken
// Grilled Station attempting to prepare Grilled Chicken...
// Grill Station: Insufficient ingredients. Replenishing ingredients...
// Grilled Station: Unable to replenish ingredients. Failed to prepare Grilled Chicken
// Oven Station attempting to prepare Grilled Chicken...
// Oven Station: Successfully prepared Grilled Chicken.

// PREPARING DISH: Beef Wellington
// Grill Station attempting to prepare Beef Wellington...
// Grill Station: Dish not available. Moving to next station...
// Oven Station attempting to prepare Beef Wellington...
// Oven Station: Dish not available. Moving to next station...
// Pasta Station attempting to prepare Beef Wellington...
// Pasta Station: Dish not available. Moving to next station...
// Salad Station attempting to prepare Beef Wellington...
// Salad Station: Dish not available. Moving to next station...
// Beef Wellington was not prepared.
// All dishes have been processed.

/**
 * Processes all dishes in the queue and displays detailed results.
 * @pre: None.
 * @post: All dishes are processed, and detailed information is displayed
(as per the format in the specifications), including station replenishments
and preparation results.
 * If a dish cannot be prepared even after replenishing ingredients, it
stays in the queue in its original order...
* i.e. if multiple dishes cannot be prepared, they will remain in the queue
in the same order
*/
void StationManager::processAllDishes()
{
    int initial_queue_size = dish_queue_.size();

    // Iterates through dish queues
    for (int i = 0; i < initial_queue_size; i++)
    {        
        Dish* dish = dish_queue_.front();
        std::cout << "PREPARING DISH: " << dish->getName() << std::endl;

        bool prepared_dishes = false;

        // Iterates through stations
        for (int j = 0; j < getLength(); j++)
        {
            KitchenStation* station = getEntry(j);

            std::cout << station->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;
            
            // Assigned dish checker
            bool assigned_dishes = false;
            for (int k = 0; k < station->getDishes().size(); k++)
            {
                if (station->getDishes()[k]->getName() == dish->getName())
                {
                    assigned_dishes = true;
                    break;
                }
            }

            // If a dish is assigned to a station pursue preparation logic
            if (assigned_dishes)
            {
                // If dish is assigned and can be prepared, output prepared
                if (station->canCompleteOrder(dish->getName()) && station->prepareDish(dish->getName()))
                {
                    std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                    dish_queue_.pop();

                    prepared_dishes = true;
                    break;
                }
                else
                {
                    // If dish is assigned and cannot be prepared, so replenishing from backup once
                    bool replenished_dishes = false;
                    std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;

                    // Replenishing ingredients from backup
                    for (int l = 0; l < dish->getIngredients().size(); l++)
                    {
                        Ingredient ingredient = dish->getIngredients()[l];

                        StationManager::addBackupIngredient(ingredient);

                        if (StationManager::replenishStationIngredientFromBackup(station->getName(), ingredient.name, ingredient.required_quantity))
                        {                        
                            replenished_dishes = true;
                        }
                    }

                    // If dishes are replenished and can be prepared, output replenished and prepared
                    if (replenished_dishes && station->canCompleteOrder(dish->getName()) && station->prepareDish(dish->getName()))
                    {
                        std::cout << station->getName() << ": Ingredients replenished." << std::endl;

                        std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                        dish_queue_.pop();

                        prepared_dishes = true;
                        break; 
                    }
                    // If dishes are not replenished, output failed to prepare
                    else
                    {
                        std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;
                    }
                }
            }
            // If dish is not assigned to a station print
            else
            {
                std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
            }
        }
        // If dish was not prepared even after replenishing
        if (!prepared_dishes)
        {
            dish_queue_.pop();
            dish_queue_.push(dish);
            std::cout << dish->getName() << " was not prepared." << std::endl;
        }
    }
    // Final indicator of code completion
    std::cout << "All dishes have been processed." << std::endl;
}

// std::cout << "PREPARING DISH: " << dish->getName() << std::endl;
// std::cout << station->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;
// std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
// std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;;
// std::cout << station->getName() << ": Ingredients replenished." << std::endl;
// std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
// std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;                    
// std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
// std::cout << dish->getName() << " was not prepared." << std::endl;
// std::cout << "All dishes have been processed." << std::endl;