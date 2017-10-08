namespace BobOnRails.Controller
{
    public interface ICartesianVector
    {
        double X { get; set; }

        double Y { get; set; }

        double Z { get; set; }

        double Length { get; }
    }
}
