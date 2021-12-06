#include "CollisionSystem.h"
#include "DataTypeMath.h"
#include "Vector2.h"
#include "CollisionComponent.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <vector>
#include <algorithm>

void Clamp(float& inVal, float min, float max)
{
	if (inVal < min) { inVal = min; }
	if (inVal > max) { inVal = max; }

}

std::vector<eae6320::CollisionComponent*> CollComponents;
std::vector<eae6320::Collision::Collider> ColliderList;


bool eae6320::Collision::AreColliding(Collider A, Collider B)
{
	eae6320::Math::Matrix4 mRot = eae6320::Math::Matrix4::CreateRotationZ(A.m_ZRot);
	eae6320::Math::Matrix4 mTrans = eae6320::Math::Matrix4::CreateTranslation(A.Location);


	eae6320::Math::Matrix4 mAToWorld = mTrans * mRot;


	eae6320::Math::Matrix4 mWorldToA = mAToWorld.GetInverse();

	mRot = eae6320::Math::Matrix4::CreateRotationZ(B.m_ZRot);
	mTrans = eae6320::Math::Matrix4::CreateTranslation(B.Location);

	eae6320::Math::Matrix4 mBToWorld = mTrans * mRot;
	eae6320::Math::Matrix4 mWorldToB = mBToWorld.GetInverse();

	eae6320::Math::Matrix4 mAToB = mWorldToB * mAToWorld;
	eae6320::Math::Matrix4 mBToA = mWorldToA * mBToWorld;
	/////////////////////////////A into B
	// a center in B
	const eae6320::Math::Vector4 AsBBCenterInB = mAToB * eae6320::Math::Vector4(A.Box.Center, 1.0f);

	//b center in a
	const eae6320::Math::Vector4 BsCenterInA = mBToA * eae6320::Math::Vector4(A.Box.Center, 1.0f);


	//a's extens while in B's space///
	const eae6320::Math::Vector4 AExtentXInB = mAToB * eae6320::Math::Vector4(A.Box.Extents.x(), 0, 0, 0);
	const eae6320::Math::Vector4 AExtentYInB = mAToB * eae6320::Math::Vector4(0, A.Box.Extents.y(), 0, 0);
	//////////
	///b's extents while inside A's space
	const eae6320::Math::Vector4 BExtentXInA = mBToA * eae6320::Math::Vector4(B.Box.Extents.x(), 0, 0, 0);
	const eae6320::Math::Vector4 BExtentYInA = mBToA * eae6320::Math::Vector4(0, B.Box.Extents.y(), 0, 0);

	///////////////////


	//new A extents
	const float AProjectionOntoB_x = fabs(AExtentXInB.x()) + fabs(AExtentYInB.x());
	const float AProjectionOntoB_y = fabs(AExtentXInB.y()) + fabs(AExtentYInB.y());
	///////////
	//new B extents
	const float BProjectionOntoA_x = fabs(BExtentXInA.x()) + fabs(BExtentYInA.x());
	const float BProjectionOntoA_y = fabs(BExtentXInA.y()) + fabs(BExtentYInA.y());
	//////////////

	float val = fabs(AsBBCenterInB.x() + A.Location.x() - B.Box.Center.x() + B.Location.x());



	//this should be equivalent to doing the point thing
	if (fabs((AsBBCenterInB.x() + A.Location.x()) - (B.Box.Center.x() + B.Location.x())) >
		fabs((AProjectionOntoB_x + B.Box.Extents.x())))
	{
		return false;
	}
	if (fabs((AsBBCenterInB.y() +A.Location.y()) - (B.Box.Center.y() + B.Location.y())) >
		fabs((AProjectionOntoB_y + B.Box.Extents.y())))
	{
		return false;
	}


	//NOW do B inside A
	val = fabs(AsBBCenterInB.x() + A.Location.x() - B.Box.Center.x() + B.Location.x());

	if (fabs((BsCenterInA.x() + B.Location.x()) - (A.Box.Center.x() + A.Location.x())) >
		fabs(((BProjectionOntoA_x + A.Box.Extents.x()))))
	{
		return false;
	}
	if (fabs((BsCenterInA.y() + B.Location.y()) - (A.Box.Center.y() + A.Location.y()) >
		fabs((BProjectionOntoA_y + A.Box.Extents.y()))))
	{
		return false;
	}

	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];
	sprintf_s(Buffer, lenBuffer, "WasCollision\n");

	return true;
}

bool eae6320::Collision::IsColliding(Collider A, Collider B, float i_dt, float& CollTime, eae6320::Math::Vector3& InCollisionAxisNormal)
{


	return false;
	/*
	eae6320::Math::Vector3 ALoc = A.Location;
	eae6320::Math::Vector3 BLoc = B.Location;

	eae6320::Math::Matrix4 mRot = eae6320::Math::Matrix4::CreateRotationZ(A.m_ZRot);
	eae6320::Math::Matrix4 mTrans = eae6320::Math::Matrix4::CreateTranslation(ALoc);


	eae6320::Math::Matrix4 mAToWorld = mTrans * mRot;


	eae6320::Math::Matrix4 mWorldToA = mAToWorld.GetInverse();

	mRot = eae6320::Math::Matrix4::CreateRotationZ(B.m_ZRot);
	mTrans = eae6320::Math::Matrix4::CreateTranslation(BLoc);

	eae6320::Math::Matrix4 mBToWorld = mTrans * mRot;
	eae6320::Math::Matrix4 mWorldToB = mBToWorld.GetInverse();

	eae6320::Math::Matrix4 mAToB = mWorldToB * mAToWorld;
	eae6320::Math::Matrix4 mBToA = mWorldToA * mBToWorld;
	/////////////////////////////A into B
	// a center in B
	const eae6320::Math::Vector4 AsBBCenterInB = mAToB * eae6320::Math::Vector4(A.Box.Center, 1.0f);

	//b center in a
	const eae6320::Math::Vector4 BsCenterInA = mBToA * eae6320::Math::Vector4(A.Box.Center, 1.0f);


	//a's extens while in B's space///
	const eae6320::Math::Vector4 AExtentXInB = mAToB * eae6320::Math::Vector4(A.Box.Extents.x(), 0, 0, 0);
	const eae6320::Math::Vector4 AExtentYInB = mAToB * eae6320::Math::Vector4(0, A.Box.Extents.y(), 0, 0);
	//////////
	///b's extents while inside A's space
	const eae6320::Math::Vector4 BExtentXInA = mBToA * eae6320::Math::Vector4(B.Box.Extents.x(), 0, 0, 0);
	const eae6320::Math::Vector4 BExtentYInA = mBToA * eae6320::Math::Vector4(0, B.Box.Extents.y(), 0, 0);

	///////////////////


	//new A extents
	const float AProjectionOntoB_x = fabs(AExtentXInB.x()) + fabs(AExtentYInB.x());
	const float AProjectionOntoB_y = fabs(AExtentXInB.y()) + fabs(AExtentYInB.y());
	///////////
	//new B extents
	const float BProjectionOntoA_x = fabs(BExtentXInA.x()) + fabs(BExtentYInA.x());
	const float BProjectionOntoA_y = fabs(BExtentXInA.y()) + fabs(BExtentYInA.y());
	//////////////

	
	eae6320::Math::Vector3 AVel = eae6320::Math::Vector3(AOwner->GetVelocity().x, AOwner->GetVelocity().y, AOwner->GetVelocity().z);
	eae6320::Math::Vector3 BVel = eae6320::Math::Vector3(BOwner->GetVelocity().x, BOwner->GetVelocity().y, BOwner->GetVelocity().z);

	eae6320::Math::Vector3 AVelRelativeToBs = AVel - BVel;
	eae6320::Math::Vector3 BVelRelativeToAs = BVel-AVel;

	eae6320::Math::Vector4 AVelInB = mWorldToB * eae6320::Math::Vector4(AVelRelativeToBs, 0.0f);
	eae6320::Math::Vector4 BVelInA = mWorldToA * eae6320::Math::Vector4(BVelRelativeToAs, 0.0f);

	

	float ATimeXClose = ((B.Box.Center.x() - B.Box.Extents.x() + BLoc.x()) - (AsBBCenterInB.x() + AProjectionOntoB_x + ALoc.x())) / AVelInB.x();

	float ATimeXOpen = ((B.Box.Center.x() + B.Box.Extents.x() + BLoc.x()) - (AsBBCenterInB.x() - AProjectionOntoB_x + ALoc.x())) / AVelInB.x();

	float ATimeYClose = ((B.Box.Center.y() - B.Box.Extents.y() + BLoc.y()) - (AsBBCenterInB.y() + AProjectionOntoB_y + ALoc.y())) / AVelInB.y();
	float ATimeYOpen = ((B.Box.Center.y() + B.Box.Extents.y() + BLoc.y()) - (AsBBCenterInB.y() - AProjectionOntoB_y + ALoc.y())) / AVelInB.y();



	float BTimeXClose = ((A.Box.Center.x() - A.Box.Extents.x() + ALoc.x()) - (BsCenterInA.x() + BProjectionOntoA_x + BLoc.x())) / BVelInA.x();
	float BTimeXOpen = ((A.Box.Center.x() + A.Box.Extents.x() + ALoc.x()) - (BsCenterInA.x() - BProjectionOntoA_x + BLoc.x())) / BVelInA.x();

	float BTimeYClose = ((A.Box.Center.y() - A.Box.Extents.y() + ALoc.y()) - (BsCenterInA.y() + BProjectionOntoA_y + BLoc.y())) / BVelInA.y();
	float BTimeYOpen = ((A.Box.Center.y() + A.Box.Extents.y() + ALoc.y()) - (BsCenterInA.y() - BProjectionOntoA_y + BLoc.y())) / BVelInA.y();






	std::vector<float> Axis;
	Axis.push_back(1);
	Axis.push_back(1);
	Axis.push_back(1);
	Axis.push_back(1);

	if (ATimeXOpen < ATimeXClose)
	{
		float Temp = ATimeXOpen;
		ATimeXOpen = ATimeXClose;
		ATimeXClose = Temp;
		Axis[0] = -1;
	}
	if (ATimeYOpen < ATimeYClose)
	{
		float Temp = ATimeYOpen;
		ATimeYOpen = ATimeYClose;
		ATimeYClose = Temp;
		Axis[1] = -1;
	}
	if (BTimeXOpen < BTimeXClose)
	{
		float Temp = BTimeXOpen;
		BTimeXOpen = BTimeXClose;
		BTimeXClose = Temp;
		Axis[2] = -1;
	}
	if (BTimeYOpen < BTimeYClose)
	{
		float Temp = BTimeYOpen;
		BTimeYOpen = BTimeYClose;
		BTimeYClose = Temp;
		Axis[3] = -1;
	}



	if (ATimeXClose > i_dt || ATimeYClose > i_dt || BTimeXClose > i_dt || BTimeYClose > i_dt)
	{
		return false;
	}
	if (ATimeXOpen < 0 || ATimeYOpen < 0 || BTimeXOpen < 0 || BTimeYOpen < 0)
	{
		return false;
	}

	Clamp(ATimeXOpen, 0, i_dt);
	Clamp(ATimeXClose, 0, i_dt);
	Clamp(ATimeYClose, 0, i_dt);
	Clamp(ATimeYOpen, 0, i_dt);
	Clamp(BTimeXOpen, 0, i_dt);
	Clamp(BTimeXClose, 0, i_dt);
	Clamp(BTimeYClose, 0, i_dt);
	Clamp(BTimeYOpen, 0, i_dt);



	std::vector<float> CloseList;
	CloseList.push_back(ATimeXClose);
	CloseList.push_back(ATimeYClose);
	CloseList.push_back(BTimeXClose);
	CloseList.push_back(BTimeYClose);

	std::vector<float> OpenList;
	OpenList.push_back(ATimeXOpen);
	OpenList.push_back(ATimeYOpen);
	OpenList.push_back(BTimeXOpen);
	OpenList.push_back(BTimeYOpen);


	float LatestClose;
	float EarliestOpen;

	LatestClose = CloseList[0];
	for (auto& it : CloseList)
	{
		if (it > LatestClose)
		{
			LatestClose = it;
		}
	}
	EarliestOpen = OpenList[0];
	for (auto& it : OpenList)
	{
		if (it < EarliestOpen)
		{
			EarliestOpen = it;
		}
	}


	if (LatestClose > EarliestOpen)
	{
		return false;
	}
	if (LatestClose < EarliestOpen)
	{
		if (LatestClose < 0) { LatestClose = 0; }

		CollTime = LatestClose;
		size_t collAxisIndex = std::find(CloseList.begin(), CloseList.end(), LatestClose) - CloseList.begin();
		if (collAxisIndex == 0 || collAxisIndex == 2) //collision was X axis
		{
			InCollisionAxisNormal = eae6320::Math::Vector3(Axis[collAxisIndex], 0, 0);
		}
		else if (collAxisIndex == 1 || collAxisIndex == 3) //collision was Y axis
		{
			InCollisionAxisNormal = eae6320::Math::Vector3(0, Axis[collAxisIndex], 0);
		}
		return true;

	}

	return false;
	*/
}

eae6320::Collision::CollisionPair FindEarliestCollision(float i_dt)
{
	eae6320::Collision::CollisionPair EarliestCollision;
	EarliestCollision.m_CollisionTime = i_dt;

	const size_t count = ColliderList.size();

	for (size_t i = 0; i < (count - 1); i++)
	{
		for (size_t j = i + 1; j < count; j++)
		{

			float colTime;
			eae6320::Math::Vector3 collisionAxisNormal;

			if (eae6320::Collision::IsColliding(ColliderList[i], ColliderList[j], i_dt, colTime, collisionAxisNormal))
			{
				if (colTime < EarliestCollision.m_CollisionTime)
				{
					EarliestCollision.m_CollisionTime = colTime;
					EarliestCollision.A = new eae6320::Collision::Collision(-collisionAxisNormal, ColliderList[i]);
					//EarliestCollision.A->m_CollisionNormal = -collisionAxisNormal;
					//EarliestCollision.A->m_CollisionObject = ColliderList[i];
					EarliestCollision.B = new eae6320::Collision::Collision(collisionAxisNormal, ColliderList[j]);
					//EarliestCollision.B->m_CollisionNormal = collisionAxisNormal;
					//EarliestCollision.B->m_CollisionObject = ColliderList[j];

				}

			}
		}
	}

	return EarliestCollision;
}

void eae6320::Collision::ResolveCollision(const CollisionPair Collision)
{
}

void eae6320::Collision::ResolveCollisions(float i_dt)
{
	float frameTimeLeft = i_dt;

	while (frameTimeLeft > 0.0f)
	{
		CollisionPair Collision = FindEarliestCollision(frameTimeLeft);

		//AdvanceSimulation(Collision.m_CollisionTime);

		if (Collision.m_CollisionTime < frameTimeLeft)
		{
			ResolveCollision(Collision);
		}
		frameTimeLeft -= Collision.m_CollisionTime;
		delete Collision.A;
		delete Collision.B;
	}
}

void eae6320::Collision::RunAllCollisionTests()
{
	eae6320::Collision::CollisionPair EarliestCollision;
	

	const size_t count = CollComponents.size();

	for (size_t i = 0; i < (count - 1); i++)
	{
		for (size_t j = i + 1; j < count; j++)
		{

			if (eae6320::Collision::AreColliding(CollComponents[i]->ColliderObject, CollComponents[j]->ColliderObject))
			{
				
				CollComponents[i]->BroadcastCallback(CollComponents[j]->ColliderObject);
				CollComponents[j]->BroadcastCallback(CollComponents[i]->ColliderObject);

			}
		}
	}
}
void eae6320::Collision::AddCollisionComponent(eae6320::CollisionComponent* i_comp)
{
	CollComponents.push_back(i_comp);
}
void eae6320::Collision::AddCollider(Collider InCollider)
{
}

