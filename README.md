# C++ E-Commerce System

This repository contains a complete, console-based e-commerce system written in C++. This project was developed as a solution for the Fawry Quantum Full Stack Development Internship Challenge.

The program simulates the core functionality of an online store, from adding products to a cart to processing a full checkout, including error handling and shipping notices.

## Design Approach

This project is built around a robust, class-based design in C++. Instead of using inheritance, it employs a single, comprehensive `Product` class that handles all product variations through multiple constructors and boolean flags (`IsShippable`, `IsExpirable`). The business logic for different product types is managed through conditional checks within the main `checkout` procedure.

This approach demonstrates strong procedural control flow and direct state management within a class-based structure.

## System Features

* **Product Catalog:** The system defines products with a name, price, and quantity.
* **Product Variations:** Handles different product types:
    * Shippable products that have a weight.
    * Products that can be marked as expirable.
    * Simple products that are neither shippable nor expirable.
* **Shopping Cart:** Customers can add a specific quantity of any available product to their cart. The system checks for available stock before adding.
* **Checkout Process:** A full checkout procedure that performs the following actions:
    * Calculates and displays the order subtotal, shipping fees, and total paid amount.
    * Handles errors for an empty cart, out-of-stock items, expired products, or insufficient customer balance.
    * Updates the customer's balance after a successful purchase.
* **Shipping Service:** A `Shipping` class processes all shippable items in an order, calculates the total weight, and prints a shipment notice.

    g++ main.cpp -o fawry_challenge
    ```
5.  Run the compiled executable:
    ```sh
    ./fawry_challenge
    ```
