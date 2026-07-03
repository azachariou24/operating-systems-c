# Synchronization Design

## Purpose

This document describes the synchronization design used in the waiter–clients example.

The program models a shared table accessed by one waiter thread and three client threads. The waiter places two food items on the table, while each client waits for the combination that completes the item they already have.

## Thread Roles

The program uses four threads:

- **Waiter thread**
  - Waits until the table is available.
  - Randomly selects one food combination.
  - Signals the client that can consume that combination.

- **Client threads**
  - Each client owns one food item permanently.
  - Each client waits on a dedicated semaphore.
  - After eating, the client releases the table.

## Shared Resource

The shared resource is the table.

Only one food combination should be available on the table at a time. This is enforced using the `table` semaphore, which acts as a binary semaphore.

When the table is free, the waiter can place a new combination. When a client starts eating, the table remains unavailable until the client signals that the meal is finished.

## Synchronization Strategy

The design uses one semaphore for table availability and three semaphores for client notification.

The waiter does not directly wake all clients. Instead, it signals only the semaphore associated with the selected food combination.

This avoids unnecessary wakeups and ensures that only the correct client proceeds.

## Summary

The design provides a simple example of semaphore-based coordination between multiple threads.

It demonstrates how semaphores can be used both for mutual exclusion and for event notification in concurrent C programs.