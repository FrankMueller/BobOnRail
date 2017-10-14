using System;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows.Threading;
using HelixToolkit.Wpf;

namespace BobOnRails.Controller.GUI
{
    /// <summary>
    /// Provides a ViewModel for the Main window.
    /// </summary>
    public class MainViewModel
    {
        private GeometryModel3D bob;

        /// <summary>
        /// Gets or sets the model.
        /// </summary>
        public Model3D Model { get; set; }

        public Point3DCollection Path { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="MainViewModel"/> class.
        /// </summary>
        public MainViewModel()
        {
            //Create some materials
            var greenMaterial = MaterialHelper.CreateMaterial(Colors.Green);
            var blueMaterial = MaterialHelper.CreateMaterial(Colors.Blue);

            //Create a mesh geometry representing Bob
            var meshBuilder = new MeshBuilder(false, false);
            meshBuilder.AddBox(new Point3D(0, 0, 0.25), 1, 2, 0.5);
            meshBuilder.AddCylinder(new Point3D(0.5, 0.5, 0.5), new Point3D(0.5, 0.5, 1.5), 0.25, 18);
            bob = new GeometryModel3D { Geometry = meshBuilder.ToMesh(true), Material = greenMaterial };

            //Create a geometry representing the path Bob travelled
            Path = new Point3DCollection();

            var grid = new GridLinesVisual3D() { Width = 10, Length = 10, MinorDistance = 1, MajorDistance = 5, Thickness = 0.01, Material = blueMaterial };
            
            //Create a model group
            var modelGroup = new Model3DGroup();
            modelGroup.Children.Add(bob);
            modelGroup.Children.Add(grid.Model);

            Model = modelGroup;

            var timer = new DispatcherTimer();
            timer.Tick += OnTimerTick;
            timer.Interval = TimeSpan.FromMilliseconds(20);
            timer.Start();
        }

        private void OnTimerTick(object sender, EventArgs e)
        {
            var random = new Random();
            var point = new Point3D(random.NextDouble(), random.NextDouble(), random.NextDouble());
            Path.Add(point);

            bob.Transform = new TranslateTransform3D(point.X, point.Y, point.Z);
        }
    }
}
