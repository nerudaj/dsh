# libperlin specification

## Usage

 * As a user, I want to instantiate PerlinNoiseGenerator for given number of dimensions and ask it for noise value at given coordinates
 * As a user, I might want to set the following:
    * Seed of the generator
    * Number of amplitudes and their coeficients
    * Number of octaves
    * Gradient complexity mode (fast orthogonal, fast diagonal, fast 8 dir, slow complete)
    * Gradient density (how many coordinates fit between two gradients)
    * Gradient array size

## Implementation

### perlin::NoiseGenerator<Dims>

 * PerlinNoiseGenerator<Dims> should be usable right after instantiation with default data (but it should be fast)
    * Internally, gradient array is generated
 * Changes to octaves and amplitudes should not affect the gradient array
 * Changes to gradient density should not affect the gradient array
 * Changes to gradient array size, complexity mode or seed should lead to repeated generation of gradient array
 * Ctors:
    * Empty (default)
    * Seed
    * Gradient array size
    * Gradient complexity mode
    * Seed, Gradient array size
    * Seed, Gradient complexity mode
    * Gradient array size, Gradient complexity mode
    * Seed, Gradient array size, Gradient complexity mode

### perlin::Vector<Dims>

 * Can only be constructed using list of numbers of concrete length
 * Has only one method getNormalizedIndex, which requires vector of dimensions as a argument

## Example

```
perlin::NoiseGenerator<2> gen(unsigned(time(NULL))); // Instantiate generator for 2 dimensions with current time as seed

// Change following to change the output
gen.setGradientDensity({2, 2});
gen.setGradientComplexity(perlin::GradientComplexity::FastOctagonal);

// Create empty map
unsigned mapWidth = 10;
unsigned mapHeight = 10;
std::vector<unsigned> map(mapWidth * mapHeight, 0);

// Fill map with value for each index
for (unsigned y = 0; y < mapHeight; y++) {
	for (unsigned x = 0; x < mapWidth; x++) {
		map[y * mapWidth + x] = static_cast<unsigned>(10.f * gen.getValueAt({x, y}));
	}
}
```

## Tests

Following can and shall be tested:

### perlin::Vector

 * Test conversion from ctor to 1 dim coordinate

### perlin::Math

 * lerp
 * dot product
 * gradient vector size
 * gradient vector normalization

### perlin::NoiseGenerator

 * Specific values for specific setup

## Documentation

 * There must be a doxydocs for public API
 * There must be a Readme.md containing examples of basic usage, basic configuration and explanation of effects of certain configurations
