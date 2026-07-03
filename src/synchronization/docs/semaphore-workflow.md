\# Semaphore Workflow



\## Overview



This document describes the synchronization workflow implemented using POSIX semaphores.



The waiter and the clients communicate exclusively through semaphore operations. This ensures that exactly one client proceeds after each waiter action while preventing concurrent access to the shared table.



\---



\## Initial State



At program startup, all semaphores are initialized as follows:



| Semaphore | Initial Value | Purpose |

| ---------- | ------------: | ------- |

| `table` | 1 | Indicates that the table is initially available. |

| `pies\_meat` | 0 | Client with vegetables waits for pies and meat. |

| `meat\_veg` | 0 | Client with pies waits for meat and vegetables. |

| `veg\_pies` | 0 | Client with meat waits for vegetables and pies. |



Initially, all clients are blocked while the waiter is allowed to place the first food combination.



\---



\## Synchronization Cycle



\### Step 1 — Wait for the Table



The waiter waits until the table becomes available.



```text

sem\_wait(table)

```



If another client is currently eating, the waiter remains blocked.



\---



\### Step 2 — Select a Food Combination



The waiter randomly selects one of three possible food combinations.



Possible combinations are:



\- Pies \& Meat

\- Meat \& Vegetables

\- Vegetables \& Pies



\---



\### Step 3 — Notify the Appropriate Client



After selecting a food combination, the waiter signals exactly one semaphore.



For example:



```text

sem\_post(pies\_meat)

```



Only the client waiting on that semaphore becomes ready to execute.



All other clients remain blocked.



\---



\### Step 4 — Client Consumes the Meal



The selected client resumes execution.



The client:



\- receives the notification,

\- starts eating,

\- simulates meal consumption,

\- keeps the table unavailable during execution.



No other client can proceed during this period.



\---



\### Step 5 — Release the Table



After finishing the meal, the client releases the shared table.



```text

sem\_post(table)

```



The waiter can now continue with the next synchronization cycle.



\---



\## Synchronization Properties



This workflow guarantees that:



\- only one food combination is present on the table,

\- only one client proceeds during each cycle,

\- the waiter waits until the previous client finishes,

\- synchronization is achieved without busy waiting,

\- semaphore operations provide safe coordination between concurrent threads.



\---



\## Summary



The synchronization workflow demonstrates a simple and efficient semaphore-based communication mechanism between multiple concurrent threads.



The design ensures deterministic coordination while keeping the implementation clean, readable, and suitable for educational operating systems projects.

