namespace SmartHome;

/// <summary>
/// Структура «Деньги» — для демонстрации разницы между
/// ссылочными типами (class) и значимыми типами (struct).
/// </summary>
public struct Money
{
    public int Rubles;
    public int Kopecks;

    public override readonly string ToString() =>
        $"{Rubles} руб. {Kopecks} коп.";
}
