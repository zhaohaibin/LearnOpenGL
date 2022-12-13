#include <glm/glm.hpp>



void calculate_tbn(const glm::vec3& pos_1, const glm::vec3& pos_2, const glm::vec3& pos_3,
	const glm::vec2& uv_1, const glm::vec2& uv_2, const glm::vec2& uv_3,
	glm::vec3& tangent, glm::vec3& bitangent, glm::vec3& normal)
{
	glm::vec3 edge_1 = pos_2 - pos_1;
	glm::vec3 edge_2 = pos_3 - pos_1;
	glm::vec2 deltaUV_1 = uv_2 - uv_1;
	glm::vec2 deltaUV_2 = uv_3 - uv_1;

	float f = 1.0f / (deltaUV_1.x * deltaUV_2.y - deltaUV_2.x* deltaUV_1.y);

	tangent.x = f * (deltaUV_2.y * edge_1.x - deltaUV_1.y * edge_2.x);
	tangent.y = f * (deltaUV_2.y * edge_1.y - deltaUV_1.y * edge_2.y);
	tangent.z = f * (deltaUV_2.y * edge_1.z - deltaUV_1.y * edge_2.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV_2.x * edge_1.x + deltaUV_1.x * edge_2.x);
	bitangent.y = f * (-deltaUV_2.x * edge_1.y + deltaUV_1.x * edge_2.y);
	bitangent.z = f * (-deltaUV_2.x * edge_1.z + deltaUV_1.x * edge_2.z);
	bitangent = glm::normalize(bitangent);

	normal = glm::cross(tangent, bitangent);
}
int main()
{
	//定义顶点
	glm::vec3 pos_1(-1.0, 1.0, 0.0);
	glm::vec3 pos_2(-1.0, -1.0, 0.0);
	glm::vec3 pos_3(1.0, -1.0, 0.0);
	glm::vec3 pos_4(1.0, 1.0, 0.0);

	//纹理坐标
	glm::vec2 uv_1(0.0, 1.0);
	glm::vec2 uv_2(0.0, 0.0);
	glm::vec2 uv_3(1.0, 0.0);
	glm::vec2 uv_4(1.0, 1.0);

	//法向量
	glm::vec3 normal_vector(0.0, 0.0, 1.0);

	//计算第一个三角形和deltaUV
	glm::vec3 edge_1 = pos_2 - pos_1;
	glm::vec3 edge_2 = pos_3 - pos_1;
	glm::vec2 deltaUV_1 = uv_2 - uv_1;
	glm::vec2 deltaUV_2 = uv_3 - uv_1;

	float f = 1.0f / (deltaUV_1.x * deltaUV_2.y - deltaUV_2.x* deltaUV_1.y);

	glm::vec3 tangent_1;
	tangent_1.x = f * (deltaUV_2.y * edge_1.x - deltaUV_1.y * edge_2.x);
	tangent_1.y = f * (deltaUV_2.y * edge_1.y - deltaUV_1.y * edge_2.y);
	tangent_1.z = f * (deltaUV_2.y * edge_1.z - deltaUV_1.y * edge_2.z);
	tangent_1 = glm::normalize(tangent_1);

	glm::vec3 bitangent_1;
	bitangent_1.x = f * (-deltaUV_2.x * edge_1.x + deltaUV_1.x * edge_2.x);
	bitangent_1.y = f * (-deltaUV_2.x * edge_1.y + deltaUV_1.x * edge_2.y);
	bitangent_1.z = f * (-deltaUV_2.x * edge_1.z + deltaUV_1.x * edge_2.z);
	bitangent_1 = glm::normalize(bitangent_1);

	glm::vec3 normal_vec = glm::cross(tangent_1, bitangent_1);
	return 0;
}