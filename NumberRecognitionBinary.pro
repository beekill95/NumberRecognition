TEMPLATE = subdirs

SUBDIRS += \
    PixelRun \
    NumberRecognition \
    SimpleNeuralNetwork \
    BoundaryRun \
    TextureRun \
    GTesting

NumberRecognition.depends = SimpleNeuralNetwork
PixelRun.depends = NumberRecognition
BoundaryRun.depends = NumberRecognition
TextureRun.depends = NumberRecognition
GTesting.depends = NumberRecognition
