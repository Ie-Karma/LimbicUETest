# Unreal Engine 5 Async Node Test

## Objective

This project demonstrates the implementation of a C++ asynchronous node in Unreal Engine 5 to detect changes in an Actor's boolean value. Upon detecting that the boolean value has become true, the listening Actor is destroyed. The solution leverages event dispatchers and avoids using tick events or timers.

## Components

### TargetActor

- **Class**: `ATargetActor`
- **Purpose**: Represents the Actor with a boolean value that changes over time.
- **Features**:
  - **Boolean Property**: `bTargetBool` (replicated).
  - **Event Dispatcher**: `OnBoolChanged` triggers when `bTargetBool` changes.
  - **Functions**:
    - `SetTargetBool(bool NewValue)`: Sets the boolean value and triggers replication.
    - `GetTargetBool() const`: Returns the current boolean value.

### ListeningActor

- **Class**: `AListeningActor`
- **Purpose**: Monitors changes in the `bTargetBool` of a `TargetActor` and destroys itself if the boolean becomes true.
- **Features**:
  - **Async Node**: Uses `UAsyncNode` to listen for boolean changes.
  - **Event Handler**: `OnBooleanChanged(bool NewValue)` is called when the boolean value changes. If `NewValue` is true, the Actor is destroyed.
  - **Cleanup**: Ensures proper cleanup of the async node upon destruction.

### AsyncNode

- **Class**: `UAsyncNode`
- **Purpose**: A Blueprint Async Action Node that listens for changes in the `bTargetBool` property of a `TargetActor`.
- **Features**:
  - **Event Dispatcher**: `OnBooleanChanged` broadcasts the new boolean value.
  - **Functions**:
    - `ListenForBoolChange(UObject* WorldContextObject, ATargetActor* InTargetActor)`: Static function to create and configure an instance of `UAsyncNode`.
    - `Activate()`: Binds the async node to the target actor's boolean change event.
    - `OnBoolChanged(bool NewValue)`: Broadcasts the change in the boolean value.

## Testing

1. **Test Level Setup (`L_Test`)**:
   - **Blueprints Created**:
     - A `BC_Listener` Blueprint derived from the `AListeningActor` class.
     - A `BC_Target` Blueprint derived from the `ATargetActor` class.
     - A `BC_SimpleListener` Blueprint for testing the async node functionality.

2. **Level Configuration**:
   - **Listeners**: Add multiple instances of the `Listener` Blueprint (derived from C++).
   - **Target**: Add a single instance of the `Target` Blueprint. It is configured to toggle its boolean value every 2 seconds via Blueprint. Additionally, its mesh color changes between red and green to visually indicate the boolean value.
   - **Simple Listener**: Add an instance of the simple `Listener` Blueprint, which implements the async node. This Blueprint changes its mesh from a sphere to a cube when the boolean value changes, demonstrating that the async node can interact with both C++ and Blueprint actors.

3. **Behavior Observation**:
   - After 2 seconds of running the level:
     - The `Target` Blueprint changes its color from red to green, indicating the boolean value is true.
     - The `Listener` Blueprints derived from C++ are destroyed when they detect the boolean change to true.
     - The simple `Listener` Blueprint changes its mesh from a sphere to a cube, showing the async node's functionality.

   - After another 2 seconds:
     - The `Target` Blueprint changes its color back to red, indicating the boolean value is false.
     - The simple `Listener` Blueprint changes its mesh back to a sphere.
   - This behavior continues in a loop, demonstrating the continuous detection and handling of boolean value changes.

This setup verifies that the C++ and Blueprint implementations of the async node work correctly and respond as expected to changes in the `TargetActor`'s boolean value.

