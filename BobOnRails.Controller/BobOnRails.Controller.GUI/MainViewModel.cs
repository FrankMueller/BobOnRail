using System.Windows.Media;
using System.Windows.Media.Media3D;
using HelixToolkit.Wpf;

namespace BobOnRails.Controller.GUI
{
    /// <summary>
    /// Provides a ViewModel for the Main window.
    /// </summary>
    public class MainViewModel
    {
        /// <summary>
        /// Gets or sets the model.
        /// </summary>
        /// <value>The model.</value>
        public Model3D Model { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="MainViewModel"/> class.
        /// </summary>
        public MainViewModel()
        {
            // Create a model group
            var modelGroup = new Model3DGroup();

            // Create a mesh builder and add a box to it
            var meshBuilder = new MeshBuilder(false, false);
            meshBuilder.AddBox(new Point3D(0, 0, 0.25), 1, 2, 0.5);
            meshBuilder.AddCylinder(new Point3D(0.5, 0.5, 0.5), new Point3D(0.5, 0.5, 1.5), 0.25, 18);

            // Create a mesh from the builder (and freeze it)
            var mesh = meshBuilder.ToMesh(true);

            // Create some materials
            var greenMaterial = MaterialHelper.CreateMaterial(Colors.Green);
            var blueMaterial = MaterialHelper.CreateMaterial(Colors.Blue);

            // Add 3 models to the group (using the same mesh, that's why we had to freeze it)
            modelGroup.Children.Add(new GeometryModel3D { Geometry = mesh, Material = greenMaterial });

            var grid = new GridLinesVisual3D() { Width = 10, Length = 10, MinorDistance = 1, MajorDistance = 5, Thickness = 0.01, Material = blueMaterial };
            modelGroup.Children.Add(grid.Model);

            // Set the property, which will be bound to the Content property of the ModelVisual3D (see MainWindow.xaml)
            Model = modelGroup;
        }
    }
}
