#nullable enable
namespace SmartHome;

/// <summary>
/// Пассивное табло (наследуется ТОЛЬКО от BaseDevice, НЕ реализует IControllable).
/// Используется для демонстрации проверки типов через is и as.
/// </summary>
public class PassiveDisplay : BaseDevice
{
    public string DisplayedText { get; set; }

    public PassiveDisplay(string name, Room room, string text)
        : base(name, room)
    {
        DisplayedText = text;
    }

    public override int PollInterval => 60;

    public override string Describe() =>
        $"Табло: {Header()} -> [Экран: \"{DisplayedText}\"]";
}
