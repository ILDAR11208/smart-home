#nullable enable
namespace SmartHome;

/// <summary>
/// Интерфейс-контракт управляемого устройства (по маске I*).
/// </summary>
public interface IControllable
{
    void TurnOn();
    void TurnOff();
    bool IsActive { get; }
    void ExecuteCommand(string command);
}
