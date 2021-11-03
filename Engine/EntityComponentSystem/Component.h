#ifndef EAE6320_COMPONENT_H
#define EAE6320_COMPONENT_H


namespace eae6320
{
	namespace ECS {
		class Component
		{
		private:

		public:
			virtual void Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

		};
	}
}


#endif