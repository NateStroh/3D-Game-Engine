#include "iApplication.h"
#include "GameObject.h"

void eae6320::Application::GameObject::SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	m_geometry->IncrementReferenceCount();
	m_effect->IncrementReferenceCount();

	auto predictedTransform = m_rigidBody.PredictFutureTransform(i_elapsedSecondCount_sinceLastSimulationUpdate);
	Graphics::AddGeometryEffectPair(m_geometry, predictedTransform, m_effect);

	m_geometry->DecrementReferenceCount();
	m_effect->DecrementReferenceCount();
}

void eae6320::Application::GameObject::UpdateRigidBody(const float i_elapsedSecondCount_sinceLastUpdate) {
	m_rigidBody.Update(i_elapsedSecondCount_sinceLastUpdate);
}
