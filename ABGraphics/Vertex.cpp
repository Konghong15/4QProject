#include "pch.h"

#define DVTX_SOURCE_FILE
#include "Vertex.h"

namespace Dvtx
{
	// VertexLayout
	const VertexLayout::Element& VertexLayout::ResolveByIndex(size_t i) const
	{
		return elements[i];
	}
	VertexLayout& VertexLayout::Append(ElementType type)
	{
		if (!Has(type))
		{
			elements.emplace_back(type, Size());
		}
		return *this;
	}
	bool VertexLayout::Has(ElementType type) const
	{
		for (auto& e : elements)
		{
			if (e.GetType() == type)
			{
				return true;
			}
		}
		return false;
	}
	size_t VertexLayout::Size() const
	{
		return elements.empty() ? 0u : elements.back().GetOffsetAfter();
	}
	size_t VertexLayout::GetElementCount() const
	{
		return elements.size();
	}
	std::vector<D3D11_INPUT_ELEMENT_DESC> VertexLayout::GetD3DLayout() const
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> desc;
		desc.reserve(GetElementCount());
		for (const auto& e : elements)
		{
			desc.push_back(e.GetDesc());
		}
		return desc;
	}
	std::string VertexLayout::GetCode() const
	{
		std::string code;
		for (const auto& e : elements)
		{
			code += e.GetCode();
		}
		return code;
	}


	// VertexLayout::Element
	VertexLayout::Element::Element(ElementType type, size_t offset)
		:
		type(type),
		offset(offset)
	{}
	size_t VertexLayout::Element::GetOffsetAfter() const
	{
		return offset + Size();
	}
	size_t VertexLayout::Element::GetOffset() const
	{
		return offset;
	}
	size_t VertexLayout::Element::Size() const
	{
		return SizeOf(type);
	}
	VertexLayout::ElementType VertexLayout::Element::GetType() const
	{
		return type;
	}

	template<VertexLayout::ElementType type>
	struct SysSizeLookup
	{
		static constexpr auto Exec()
		{
			return sizeof(VertexLayout::Map<type>::SysType);
		}
	};
	constexpr size_t VertexLayout::Element::SizeOf(ElementType type)
	{
		return Bridge<SysSizeLookup>(type);
	}

	template<VertexLayout::ElementType type>
	struct CodeLookup
	{
		static constexpr auto Exec()
		{
			return VertexLayout::Map<type>::code;
		}
	};
	const char* Dvtx::VertexLayout::Element::GetCode() const
	{
		return Bridge<CodeLookup>(type);
	}

	template<VertexLayout::ElementType type> struct DescGenerate {
		static constexpr D3D11_INPUT_ELEMENT_DESC Exec(size_t offset) {
			return {
				VertexLayout::Map<type>::semantic,0,
				VertexLayout::Map<type>::dxgiFormat,
				0,(UINT)offset,D3D11_INPUT_PER_VERTEX_DATA,0
			};
		}
	};
	D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::GetDesc() const
	{
		return Bridge<DescGenerate>(type, GetOffset());
	}


	// Vertex
	Vertex::Vertex(char* pData, const VertexLayout& layout)
		:
		pData(pData),
		layout(layout)
	{
		assert(pData != nullptr);
	}
	ConstVertex::ConstVertex(const Vertex& v)
		:
		vertex(v)
	{}


	// VertexBuffer
	VertexBuffer::VertexBuffer(VertexLayout layout, size_t size)
		:
		layout(std::move(layout))
	{
		Resize(size);
	}
	void VertexBuffer::Resize(size_t newSize)
	{
		const auto size = Size();
		if (size < newSize)
		{
			buffer.resize(buffer.size() + layout.Size() * (newSize - size));
		}
	}
	const char* VertexBuffer::GetData() const
	{
		return buffer.data();
	}

	template<VertexLayout::ElementType type>
	struct AttributeAiMeshFill
	{
		static constexpr void Exec(VertexBuffer* pBuf, const aiMesh& mesh)
		{
			for (auto end = mesh.mNumVertices, i = 0u; i < end; i++)
			{
				(*pBuf)[i].Attr<type>() = VertexLayout::Map<type>::Extract(mesh, i);
			}
		}
	};
	VertexBuffer::VertexBuffer(VertexLayout layout_in, const aiMesh& mesh)
		: layout(std::move(layout_in))
	{
		Resize(mesh.mNumVertices);

		for (size_t i = 0, end = layout.GetElementCount(); i < end; i++)
		{
			VertexLayout::Bridge<AttributeAiMeshFill>(layout.ResolveByIndex(i).GetType(), this, mesh);
		}
	}
	const VertexLayout& VertexBuffer::GetLayout() const
	{
		return layout;
	}
	size_t VertexBuffer::Size() const
	{
		return buffer.size() / layout.Size();
	}
	size_t VertexBuffer::SizeBytes() const
	{
		return buffer.size();
	}
	Vertex VertexBuffer::Back()
	{
		assert(buffer.size() != 0u);
		return Vertex{ buffer.data() + buffer.size() - layout.Size(),layout };
	}
	Vertex VertexBuffer::Front()
	{
		assert(buffer.size() != 0u);
		return Vertex{ buffer.data(),layout };
	}
	Vertex VertexBuffer::operator[](size_t i)
	{
		assert(i < Size());
		return Vertex{ buffer.data() + layout.Size() * i,layout };
	}
	ConstVertex VertexBuffer::Back() const
	{
		return const_cast<VertexBuffer*>(this)->Back();
	}
	ConstVertex VertexBuffer::Front() const
	{
		return const_cast<VertexBuffer*>(this)->Front();
	}
	ConstVertex VertexBuffer::operator[](size_t i) const
	{
		return const_cast<VertexBuffer&>(*this)[i];
	}
}