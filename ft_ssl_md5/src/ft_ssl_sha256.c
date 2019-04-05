#include "ft_ssl.h"

static unsigned char	g_padding[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void	ft_ssl_sha256_checksum(const char *str, t_flags *flag)
{
	t_ssl_sha256_ctx	context;
	t_byte				digest[32];

	ft_ssl_sha256_init(&context);
	ft_ssl_sha256_update(&context, (unsigned char *)str, ft_strlen(str));
	ft_ssl_sha256_final(digest, &context);
	flag->checksum = ft_strnew(64);
	ft_ssl_md5_make_string(digest, flag->checksum, 32);
}

void	ft_ssl_sha256_init(t_ssl_sha256_ctx *context)
{
	context->st[0] = 0x6a09e667;
	context->st[1] = 0xbb67ae85;
	context->st[2] = 0x3c6ef372;
	context->st[3] = 0xa54ff53a;
	context->st[4] = 0x510e527f;
	context->st[5] = 0x9b05688c;
	context->st[6] = 0x1f83d9ab;
	context->st[7] = 0x5be0cd19;
	context->num_of_bits[0] = 0;
	context->num_of_bits[1] = 0;
}

void	ft_ssl_sha256_update(t_ssl_sha256_ctx *context, t_byte *str, unsigned int str_len)
{
	unsigned int	i;
	unsigned int	curr_index;
	unsigned int	part_length;

	curr_index = (unsigned int)((context->num_of_bits[0] >> 3) & 63);
	if ((context->num_of_bits[0] += ((uint32_t)str_len << 3)) < ((uint32_t)str_len << 3))
		context->num_of_bits[1]++;
	context->num_of_bits[1] += ((uint32_t)str_len >> 29);
	part_length = FT_SHA256_BUFFER_SIZE - curr_index;
	if (str_len >= part_length)
	{
		ft_memcpy(&context->buffer[curr_index], str, part_length);
		ft_ssl_sha256_transform(context->st, context->buffer);
		i = part_length;
		while (i + 63 < str_len)
		{
			ft_ssl_sha256_transform(context->st, &str[i]);
			i += FT_SHA256_BUFFER_SIZE;
		}
		curr_index = 0;
	}
	else
		i = 0;
	ft_memcpy(&context->buffer[curr_index], &str[i], str_len - i);
}

void	ft_ssl_sha256_final(t_byte digest[32], t_ssl_sha256_ctx *context)
{
	t_byte			bits[8];
	unsigned int	curr_index;
	unsigned int	pad_length;

	ft_ssl_sha256_encode_num_of_bits(bits, context->num_of_bits, 8);
	curr_index = (unsigned int)((context->num_of_bits[0] >> 3) & 63);
	pad_length = (curr_index < 56) ? (56 - curr_index) : (120 - curr_index);
	ft_ssl_sha256_update(context, g_padding, pad_length);
	ft_ssl_sha256_update(context, bits, 8);
	ft_ssl_sha256_encode(digest, context->st, 32);
	ft_bzero(context, sizeof(t_ssl_sha256_ctx));
}
